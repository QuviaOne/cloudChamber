const SerialPort = require('serialport');
const config = require('../config.json');
const { Frame, FrameManager } = require('./frame.js');
class Connection extends SerialPort {
    constructor() {
        super(config.portPath, {
            autoOpen: false,
            baudRate: config.baudRate
        });
        this.parser = new SerialPort.parsers.Readline(config.newLineChar);
        this.pipe(this.parser);
        this.resetMemory();
        /**
         * @type {FrameManager}
         */
        this.frames = new FrameManager();
        this.parser.on("data", data => {
            if (data == "reset") return this.resetMemory();
            try {
                data = JSON.parse(data);
                if (data.id == "frame") return this.onFrame(data);
            } catch (e) {
                console.log(data);
            }
        })
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
    /**
     * 
     * @param {Number} power 
     */
    async setPWM(power) {
        this.pwmPower = new Ratio(power);
        await this.writeLine("_pwm " + this.pwmPower.toRange(0, 255));
    }
    /**
     * 
     * @param {FrameManager} frameManager 
     */
    startAutomaticPWM(frameManager) {
        this.pwmAutomatic = true;
    }
    stopAutomaticPWM() {
        this.pwmAutomatic = false;
    }
    resetMemory() {
        this.pumpRunning = false;
        this.fanRunning = false;
        this.compressorRunning = false;
    }
    onFrame(frameData) {
        this.frames.addFrame(frameData);
        if (this.pwmAutomatic) this.pwmFeedbackLoop();
    }
    /**
     * @private
     */
    pwmFeedbackLoop() {
        console.log(this.frames.length);
    }
}
module.exports.Connection = Connection;
class Ratio extends Number {
    /**
     * 
     * @param {Number} a 
     * @param {Number} b 
     */
    constructor(a, b) {
        if (!a) super(1); else if (!b) super(a); else super(a / b);
    }
    /**
     * 
     * @param {Number} max
     * @param {Number} min
     * @returns {Number}
     */
    toRange(max, min = 0) {
        return Math.round(this * (max - min) + min);
    }
    /**
     * @returns {Number}
     */
    toPercent() {
        return this * 100;
    }
    /**
     * @returns {String}
     */
    toPercentString() {
        return (this * 100) + "%";
    }

}