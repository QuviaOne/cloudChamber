const Serial = require('./modules/serialModule')
const onFrame = require('./onFrame')

async function main() {
    var l = new Serial.Connection();
    l.parser.on("data", async data=> {
        try {
            data = JSON.parse(data);
            if (data.id == "frame") return onFrame(data);
        } catch (e) {
            console.log(data);
        }
        
    })
    await l.start();
}
main();