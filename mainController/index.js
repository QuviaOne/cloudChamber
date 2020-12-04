const Serial = require('./modules/serialModule')

async function main() {
    var l = new Serial.Connection();
    l.onData = data => {
        console.log(JSON.parse(data));
    }
    await l.start();
}
main();