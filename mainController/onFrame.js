const { Frame, FrameManager } = require('./modules/frame')
const fm = new FrameManager();
module.exports = async frame => {
    // console.log(frame.temps);
    
    fm.addFrame(frame);
    if (fm.length % 30 == 0) {
        console.log(fm.lastFrame().temps)
    }
}