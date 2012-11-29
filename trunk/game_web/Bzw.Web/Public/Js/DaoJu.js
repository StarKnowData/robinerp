
/* 道具购买功能页面JS代码 杨大胜 2009-3-13 */
function btnBuyDj(djid,djname,vipprice,price,moneyname){
    var msgfix = '道具购买：'+djname+"\n\n";
    var txt = document.getElementById('txtdj'+djid);
    if(!alertNull(txt,msgfix+'购买数量不能为空！')){
        txt.focus();
        return;
    }
    else if(!/^([0-9])[0-9]*(\.\w*)?$/.test(txt.value.trim())){
        alert(msgfix+'购买数量必须是数字，并且大于零！');
        txt.focus();
        return;
    }else if(parseInt(txt.value.trim()) ==0 ){
        alert(msgfix+'购买数量必须是数字，并且大于零！');
        txt.focus();
        return;
    }
    //1.判断用户是否登录了，否就提示登录
    var urlData = '/Public/XmlHttpUser.aspx?type=islogin';
    //alert(urlData);
    var strReturn = AjaxCall(urlData);
    //alert(strReturn);
    if(strReturn=="0"){
        alert(msgfix+'对不起，请您登录后再购买。');
        return;
    }else if(strReturn=="1"){
        if(!confirm(msgfix+'确认购买该道具吗？')){
         return;
        }
    }
    //2.根据数量乘于价格的结果，判断用户是否有足够的积分（银行或钱包）buydaoju
    urlData = '/Public/XmlHttpUser.aspx?type=buydaoju&id='+djid;
    urlData += '&vipprice='+vipprice;
    urlData += '&price='+price;
    urlData += '&count='+txt.value.trim();
    //alert(urlData);
    strReturn = AjaxCall(urlData);
    //alert(strReturn);
    if (strReturn == "notmoney") {
     
        alert(msgfix+"对不起，您的银行"+moneyname+"不够购买此道具。");
    }else if(strReturn=="buycg"){
        alert(msgfix+'道具购买成功,您可以在游戏里使用它了！');
        txt.value = 1;
        //重新获取用户银行的积分数量，修改登录面板里的金额数
        var murl = '/Public/XmlHttpUser.aspx?type=lgusermoney';
        var bmoney = AjaxCall(murl);
        //alert(bmoney);
        try{
            var lgbank = document.getElementById('lgbank');
            //alert(lgbank.innerText);
            lgbank.innerText = bmoney+moneyname;
        }catch(e){}
    }else{
        alert(msgfix+'抱歉，道具购买失败，可能是服务器繁忙，请稍候再试！');
    }
}