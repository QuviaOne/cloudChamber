const SerialPort = require('serialport');
const config = require('../config.json');
class Connection extends SerialPort {
    constructor() {
        super(config.portPath, {
            autoOpen: false,
            baudRate: config.baudRate 
        });
        this.parser = new SerialPort.parsers.Readline(config.newLineChar);
        this.pipe(this.parser);
    }
    /**
     * @returns {Promise<void>}
     */
    start() {
        return new Promise((resolve, reject) => {
            this.open();
            this.on("open", resolve);
        })
    }
    /**
     * 
     * @param {String} text 
     */
    writeLine(text) {
        return new Promise((resolve, reject) => {
            this.write(text + "\n", resolve);
        })
    }
}
module.exports.Connection = Connection;