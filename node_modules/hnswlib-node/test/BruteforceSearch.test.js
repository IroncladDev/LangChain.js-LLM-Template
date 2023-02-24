const { BruteforceSearch } = require('../lib');

describe('BruteforceSearch', () => {
  describe('#constructor', () => {
    it('throws an error if no arguments are given', () => {
      expect(() => { new BruteforceSearch() }).toThrow('Expected 2 arguments, but got 0.');
    });

    it('throws an error if given a non-String object to first argument', () => {
      expect(() => { new BruteforceSearch(1, 3) }).toThrow('Invalid the first argument type, must be a string.');
    });

    it('throws an error if given a non-Number object to second argument', () => {
      expect(() => { new BruteforceSearch('l2', '3') }).toThrow('Invalid the second argument type, must be a number.');
    });

    it('throws an error if given a String that is neither "l2" nor "ip" to first argument', () => {
      expect(() => { new BruteforceSearch('cos', 3) }).toThrow('Wrong space name, expected "l2" or "ip".');
    });
  });

  describe('#initIndex', () => {
    const index = new BruteforceSearch('l2', 3);

    it('throws an error if no arguments are given', () => {
      expect(() => { index.initIndex() }).toThrow('Expected 1 arguments, but got 0.');
    });

    it('throws an error if given a non-Number argument', () => {
      expect(() => { index.initIndex('5') }).toThrow('Invalid the first argument type, must be a number.');
    });
  });

  describe('#getMaxElements', () => {
    const index = new BruteforceSearch('l2', 3);

    it('returns 0 if called before the index is initialized', () => {
      expect(index.getMaxElements()).toBe(0);
    });

    it('returns maximum number of elements', () => {
      index.initIndex(10);
      expect(index.getMaxElements()).toBe(10);
    });
  });

  describe('#getCurrentCount', () => {
    const index = new BruteforceSearch('l2', 3);

    it('returns 0 if called before the index is initialized', () => {
      expect(index.getCurrentCount()).toBe(0);
    });

    it('returns current number of elements', () => {
      index.initIndex(5);
      index.addPoint([1, 2, 3], 0);
      index.addPoint([2, 3, 4], 1);
      expect(index.getCurrentCount()).toBe(2);
    });
  });

  describe('#getNumDimensions', () => {
    const index = new BruteforceSearch('l2', 3);

    it('returns number of dimensions', () => {
      expect(index.getNumDimensions()).toBe(3);
    });
  });

  describe('#addPoint', () => {
    const index = new BruteforceSearch('l2', 3);

    it('throws an error if no arguments are given', () => {
      expect(() => { index.addPoint() }).toThrow('Expected 2 arguments, but got 0.');
    });

    it('throws an error if given a non-Array object to first argument', () => {
      expect(() => { index.addPoint('[1, 2, 3]', 0) }).toThrow('Invalid the first argument type, must be an Array.');
    });

    it('throws an error if given a non-Number object to second argument', () => {
      expect(() => { index.addPoint([1, 2, 3], '0') }).toThrow('Invalid the second argument type, must be a number.')
    });

    it('throws an error if called before the index is initialized', () => {
      expect(() => { index.addPoint([1, 2, 3], 0) }).toThrow('Search index has not been initialized, call `initIndex` in advance.');
    });

    it('throws an error if given an array with a length different from the number of dimensions', () => {
      index.initIndex(1);
      expect(() => { index.addPoint([1, 2, 3, 4, 5], 0) }).toThrow('Invalid the given array length (expected 3, but got 5).');
    });

    it('throws an error if more element is added than the maximum number of elements.', () => {
      index.initIndex(1);
      index.addPoint([1, 2, 3], 0);
      expect(() => { index.addPoint([1, 2, 3], 1) }).toThrow(/Hnswlib Error/);
    });
  });

  describe('#removePoint', () => {
    const index = new BruteforceSearch('l2', 3);

    it('throws an error if no arguments are given', () => {
      expect(() => { index.removePoint() }).toThrow('Expected 1 arguments, but got 0.');
    });

    it('throws an error if given a non-Number argument', () => {
      expect(() => { index.removePoint('0') }).toThrow('Invalid the first argument type, must be a number.');
    });

    it('throws an error if called before the index is initialized', () => {
      expect(() => { index.removePoint(0) }).toThrow('Search index has not been initialized, call `initIndex` in advance.');
    });

    it('removes the element specified by index', () => {
      index.initIndex(2);
      index.addPoint([1, 2, 3], 0);
      index.addPoint([1, 2, 4], 1);
      expect(index.getCurrentCount()).toBe(2);
      index.removePoint(1);
      expect(index.getCurrentCount()).toBe(1);
      expect(index.searchKnn([1, 2, 4], 1).neighbors).toEqual([0]);
    });
  });

  describe('#searchKnn', () => {
    describe('when metric space is "l2"', () => {
      const index = new BruteforceSearch('l2', 3);

      beforeAll(() => {
        index.initIndex(3);
        index.addPoint([1, 2, 3], 0);
        index.addPoint([2, 3, 4], 1);
        index.addPoint([3, 4, 5], 2);
      });

      it('throws an error if no arguments are given', () => {
        expect(() => { index.searchKnn() }).toThrow('Expected 2-3 arguments, but got 0.');
      });

      it('throws an error if given a non-Array object to first argument', () => {
        expect(() => { index.searchKnn('[1, 2, 3]', 2) }).toThrow('Invalid the first argument type, must be an Array.');
      });

      it('throws an error if given a non-Number object to second argument', () => {
        expect(() => { index.searchKnn([1, 2, 3], '2') }).toThrow('Invalid the second argument type, must be a number.');
      });

      it('throws an error if given a non-Function object to third argument', () => {
        expect(() => { index.searchKnn([1, 2, 3], 2, 'fnc') }).toThrow('Invalid the third argument type, must be a function.');
      });

      it('throws an error if given the number of neighborhoods exceeding the maximum number of elements', () => {
        expect(() => { index.searchKnn([1, 2, 5], 4) }).toThrow('Invalid the number of k-nearest neighbors (cannot be given a value greater than `maxElements`: 3).');
      });

      it('throws an error if given an array with a length different from the number of dimensions', () => {
        expect(() => { index.searchKnn([1, 2, 5, 4], 2) }).toThrow('Invalid the given array length (expected 3, but got 4).');
      });

      it('returns search results based on squared Euclidean distance', () => {
        expect(index.searchKnn([1, 2, 5], 2)).toMatchObject({ distances: [ 3, 4 ], neighbors: [ 1, 0 ] });
      });
    });

    describe('when metric space is "ip"', () => {
      const index = new BruteforceSearch('ip', 3);

      beforeAll(() => {
        index.initIndex(3);
        index.addPoint([1, 2, 3], 0);
        index.addPoint([2, 3, 4], 1);
        index.addPoint([3, 4, 5], 2);
      });

      it('returns search results based on one minus inner product', () => {
        expect(index.searchKnn([1, 2, 5], 2)).toMatchObject({ distances: [ -35, -27 ], neighbors: [ 2, 1 ] });
      });
    });

    describe('when filter function is given', () => {
      const index = new BruteforceSearch('l2', 3);
      const filter = (label) => label % 2 == 0;

      beforeAll(() => {
        index.initIndex(4);
        index.addPoint([1, 2, 3], 0);
        index.addPoint([1, 2, 5], 1);
        index.addPoint([1, 2, 4], 2);
        index.addPoint([1, 2, 5], 3);
      });

      it('returns filtered search results', () => {
        expect(index.searchKnn([1, 2, 5], 4, filter)).toMatchObject({ distances: [1, 4], neighbors: [2, 0] });
      });
    });
  });
});
