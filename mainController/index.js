const Serial = require('./modules/serialModule.js');
const conn = new Serial.Connection();
/**
 * @type {Serial.Connection}
 */
async function main() {
    await conn.start();
    conn.startAutomaticPWM();
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
    if (data == "pump") return conn.togglePump();
    if (data == "fan") return conn.toggleFan();
    if (data == "compressor") return conn.toggleCompressor();
    if (data == "cpeltier" || data == "pelt") return conn.togglePeltier();
    if (data == "pwmAuto") if (conn.pwmAutomatic) conn.stopAutomaticPWM(); else conn.startAutomaticPWM();
    if (data.split(" ")[0] == "pwm") conn.setPWM(Number(data.split(" ")[0]) / 255)
})