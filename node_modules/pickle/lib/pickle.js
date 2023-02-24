var spawn = require('child_process').spawn;

module.exports.loads = function loads(pickle, callback)
{
    var convert = spawn('/usr/bin/env', ['python', __dirname + '/convert.py', '--loads']),
        stdout_buffer = [];
    
    convert.stdout.on('data', function(data)
    {
        stdout_buffer.push(data);
    });
    convert.on('exit', function(code)
    {
        var data = stdout_buffer.join('');
        
        callback(
            data === '-1'
                ? false
                : JSON.parse(data)
        );
    });
    
    convert.stdin.write(pickle);
    convert.stdin.end();
};

module.exports.dumps = function dumps(raw, callback)
{
    var convert = spawn('/usr/bin/env', ['python', __dirname + '/convert.py', '--dumps']),
        stdout_buffer = [];
    
    convert.stdout.on('data', function(data)
    {
        stdout_buffer.push(data);
    });
    convert.on('exit', function(code)
    {
        var data = stdout_buffer.join('');
        
        callback(
            data === '-1'
                ? false
                : data
        );
    });
    
    convert.stdin.write(JSON.stringify(raw));
    convert.stdin.end();
};