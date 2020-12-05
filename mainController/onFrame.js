const { Frame, FrameManager } = require('./modules/frame');
const fm = new FrameManager();
module.exports = async (frame, connection) => {
    // console.log(frame.temps);
    fm.addFrame(frame);
    
}