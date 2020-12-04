const Serial = require('./modules/serialModule');
const onFrame = require('./onFrame');
/**
 * @type {Serial.Connection}
 */
var l = new Serial.Connection();
l.parser.on("data", async data => {
    if (data == "reset") return l.resetMemory();
    try {
        data = JSON.parse(data);
        if (data.id == "frame") return onFrame(data);
    } catch (e) {
        console.log(data);
    }

});
async function main() {
    
    await l.start();
    console.log("Huh")

}
main();
/**
 * 
 * @param {Number} ms 
 * @returns {Promise<void>}
 */
function wait(ms) {
    return new Promise((resolve, reject) => {
        setTimeout(resolve, ms)
    })
}


process.stdin.on("data", data => {
    data = data.toString().split("\r\n")[0];
    if (data == "pump") return l.togglePump();
    if (data == "fan") return l.toggleFan();
    if (data == "compressor") return l.toggleCompressor();
})