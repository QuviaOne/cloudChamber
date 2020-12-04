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
        this.resetMemory();
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
    async togglePump() {
        this.pumpRunning = !this.pumpRunning;
        await this.writeLine("_2");
    }
    async toggleCompressor() {
        this.compressorRunning = !this.compressorRunning;
        await this.writeLine("_3");
    }
    async toggleFan() {
        this.fanRunning = !this.fanRunning;
        await this.writeLine("_1");
    }
    resetMemory() {
        this.pumpRunning = false;
        this.fanRunning = false;
        this.compressorRunning = false;
    }
}
module.exports.Connection = Connection;