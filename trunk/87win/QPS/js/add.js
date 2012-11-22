function initEcAd() {

document.all.AdLayer2.style.posTop = -200;
document.all.AdLayer2.style.visibility = 'visible'
document.all.AdLayer1.style.posTop = -200;
document.all.AdLayer1.style.visibility = 'visible'
MoveLeftLayer('AdLayer1');
MoveRightLayer('AdLayer2');
}
function MoveLeftLayer(layerName) {
var x = 900;
var y =100;// 左侧广告距离页首高度
var diff = (document.body.scrollTop + y - document.all.AdLayer1.style.posTop)*.40;
var y = document.body.scrollTop + y - diff;
eval("document.all." + layerName + ".style.posTop = y");
eval("document.all." + layerName + ".style.posRight = x");
setTimeout("MoveLeftLayer('AdLayer1');", 20);
}
function MoveRightLayer(layerName) {
var x = 5;
var y = 100;// 右侧广告距离页首高度
var diff = (document.body.scrollTop + y - document.all.AdLayer2.style.posTop)*.40;
var y = document.body.scrollTop + y - diff;
eval("document.all." + layerName + ".style.posTop = y");
eval("document.all." + layerName + ".style.posRight = x");
setTimeout("MoveRightLayer('AdLayer2');", 20);
}

document.write("<div id=AdLayer1 style='position: absolute;visibility:hidden;z-index:1;'></div>"+"<div id=AdLayer2 style='position: absolute;visibility:hidden;z-index:1'><table width='95' height='471' border='0' cellspacing='0' cellpadding='0' background='images/kf_r2_c2.jpg'><tr><td valign='top' ><table width='85' border='0' align='center' cellpadding='0' cellspacing='0'><tr><td height='29'>&nbsp;</td></tr><tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser001@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser002@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser003@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser004@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser005@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser006@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser007@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser008@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr> <tr><td height='24' style='font-size: 14px'>MSN:<A HREF='msnim:chat?contact=perfectlaser@hotmail.com'> <IMG SRC='images/msn.gif' align='absmiddle' border='0' ALT='MSN Online Status Indicator'></A></td></tr><tr><td height='24' valign=top>skype:<br/><script type='text/javascript' src='http://skype.tom.com/script/skypeCheck40.js'></script><a href='skype:jiaxinlaser?add' target='blank' target='blank'><img src=images/small_white_online.png border='0'/></a><script type='text/javascript' src='http://skype.tom.com/script/skypeCheck40.js'></script><a href='skype:Perfectlaser001?add' target='blank' target='blank'><img src=images/small_white_online.png border='0'/></a><script type='text/javascript' src='http://skype.tom.com/script/skypeCheck40.js'></script><a href='skype:perfectlaser004?add' target='blank' target='blank'><img src=images/small_white_online.png border='0'/></a><br/><script type='text/javascript' src='http://skype.tom.com/script/skypeCheck40.js'></script><a href='skype:perfectlaser005?add' target='blank' target='blank'><img src=images/small_white_online.png border='0'/></a><script type='text/javascript' src='http://skype.tom.com/script/skypeCheck40.js'></script><a href='skype:PerfectLaserCathy?add' target='blank' target='blank'><img src=images/small_white_online.png border='0'/></a><script type='text/javascript' src='http://download.skype.com/share/skypebuttons/js/skypeCheck.js'></script><a href='skype:perfectlaser005?add' target='blank'><img src=images/small_white_online.png border='0'/></a></td></tr><tr><td height='20'></td></tr><tr><td>&nbsp;</td></tr></table></td></tr></table></div>");
initEcAd()// JavaScript Document