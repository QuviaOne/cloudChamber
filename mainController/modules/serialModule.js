const { Resolver } = require('dns');
const SerialPort = require('serialport');
const config = require('../config.json');
module.exports = {
    /**
     * @return {Promise<void>}
     */
    init: () => {
        return new Promise((resolve, reject) => {
            module.exports.serialPort = new SerialPort(config.portPath, { 
                autoOpen: false,
                baudRate: 57600
            });
            module.exports.serialPort.on("open", () => {
                resolve();
            })
            module.exports.serialPort.open(reject);
        });
    }
}