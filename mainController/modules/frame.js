class Frame {
    /**
     * @param {FrameManager} frameManager
     * @param {Array<Number>} temps 
     */
    constructor(frameManager, temps) {
        /**
         * @type {FrameManager}
         */
        this.manager = frameManager;
        /**
         * @type {Array<Number>}
         */
        this.temps = temps;
        this.timestamp = new Date().getTime();
    }
}
class FrameManager extends Array {
    constructor() {
        super();
    }
    addFrame(obj) {
        if (this.length > 1e6) this.splice(0, 1);
        this.push(new Frame(this, obj.temps));
    }
    /**
     * 
     * @param {Array} arr 
     */
    static from(arr) {
        var rv = new this();
        for (var a of arr) {
            rv.addFrame(a);
        }
        return rv;
    }
    /**
     * @returns {Frame}
     */
    lastFrame() {
        return this[this.length - 1];
    }
}
module.exports.Frame = Frame;
module.exports.FrameManager = FrameManager;
