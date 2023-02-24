## [[1.3.0](https://github.com/yoshoku/hnswlib-node/compare/v1.2.0...v1.3.0)] - 2023-02-19

- Updete bundled hnswlib to v0.7.0.
- Add support for named arguments in `initIndex` of HierarchicalNSW.
- Add support for replacing an element marked for deletion with a new element.
  ```javascript
  import { HierarchicalNSW } from 'hnswlib-node';

  const index = new HierarchicalNSW('l2', 3);
  index.initIndex({ maxElements: 2, allowReplaceDeleted: true });

  index.addPoint([1, 2, 3], 0)
  index.addPoint([4, 5, 6], 1)

  // adding deletion mark to the label `1` element.
  index.markDelete(1);

  // replacing with new label `1` element by specifying true to the third argument.
  index.addPoint([6, 5, 4], 1, true);
  ```
- Add support filtering function by label in `searchKnn` of BruteforeceSearch and HierarchicalNSW.
  ```javascript
  import { HierarchicalNSW } from 'hnswlib-node';

  const index = new HierarchicalNSW('l2', 3);
  index.initIndex({ maxElements: 4 });

  index.addPoint([1, 2, 3], 1)
  index.addPoint([1, 3, 3], 2)
  index.addPoint([1, 2, 3], 3)
  index.addPoint([1, 3, 3], 4)

  // setting filter funtion that allows only even labels.
  const filter = (label: number): boolean => label % 2 == 0;
  console.table(index.searchKnn([1, 2, 3], 2, filter));
  // ┌───────────┬───┬───┐
  // │  (index)  │ 0 │ 1 │
  // ├───────────┼───┼───┤
  // │ distances │ 1 │ 1 │
  // │ neighbors │ 2 │ 4 │
  // └───────────┴───┴───┘
  ```
- Remove deprecated functions `loadIndex` and `saveIndex` from BruteforeceSearch and HierarchicalNSW.
- Update dev-dependencies.

## [[1.2.0](https://github.com/yoshoku/hnswlib-node/compare/v1.1.0...v1.2.0)] - 2022-11-26

- Update dependencies: node-addon-api@5.0.0.
- Update dev-dependencies.

## [[1.1.0](https://github.com/yoshoku/hnswlib-node/compare/v1.0.3...v1.1.0)] - 2022-04-29

- Add `readIndex`, `writeIndex`, `readIndexSync`, and `writeIndexSync` functions to BruteforeceSearch and HierarchicalNSW.
- Deprecate `loadIndex` and `saveIndex` functions on BruteforeceSearch and HierarchicalNSW,
use `readIndexSync` and `writeIndexSync` instead.

## [[1.0.3](https://github.com/yoshoku/hnswlib-node/compare/v1.0.2...v1.0.3)] - 2022-04-14

- Change array type notation in declaration file.

## [[1.0.2](https://github.com/yoshoku/hnswlib-node/compare/v1.0.1...v1.0.2)] - 2022-03-21

- Change to call the constructor when loading the search index on the BruteforeceSearch class.
- Fix to use the member variable of the original BruteforeceSearch class for the maximum number of elements.

## [[1.0.1](https://github.com/yoshoku/hnswlib-node/compare/v1.0.0...v1.0.1)] - 2022-03-19

- Add API documentation.

## [1.0.0] - 2022-03-13

- Initial release.
