// JScript 文件

/* 随机时间 */
function getDataTime()
{
	var strDate,strTime;
	strDate = new Date();
	strTime = strDate.getTime();
	return strTime;
}

/* 正则表达表 */
function RegTest(TestStr, RegExpStr)
{
	return RegExpStr.test(TestStr)
}

/* 截取固定长度子字符串 sSource为字符串iLen为长度 */
function getInterceptedStr(sSource, iLen)
{
    if(sSource.replace(/[^\x00-\xff]/g,"xx").length <= iLen)
    {
        return sSource;
    }
    var str = "";
    var l = 0;
    var schar;
    for(var i=0; schar=sSource.charAt(i); i++)
    {
        str += schar;
        l += (schar.match(/[^\x00-\xff]/) != null ? 2 : 1);
        if(l >= iLen)
        {
            break;
        }
    }
    return str;
}



/* 检测用户名 */
function checkUserName(ActionFlag)
{
    var Element = document.getElementById('username');
    var Elements = document.getElementById("unamespan");
    if (ActionFlag == 0)
    {
        Element.keytype = 'No';
        Elements.className = 'notetrue';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 用户名由5-20个英文字母或数字组成。';
    }
    else
    {
        if(!RegTest(Element.value, /^[0-9a-zA-Z]{5,20}$/))
        {
            Element.keytype = 'No';
	        Elements.className = 'noteerror';
            Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 用户名由5-20个英文字母或数字组成。';
	    }
        else
        {
            requestSimpleService = UserService.getUser(Element.value, OnRequestUser);
        }
    }
}

/* 验证用户名结果 */
function OnRequestUser(result)
{
    var Element = document.getElementById('username');
    var Elements = document.getElementById("unamespan");
    if(result)
    {
        Element.keytype = 'No';
        Elements.className = 'noteerror';
        Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 对不起，该用户名已经存在。';
    }
    else
    {
        Element.keytype = 'Yes';
        Elements.className = 'note';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，该用户名可以注册。'; 
    }
}

/* 检测昵称 */
function checkNickName(ActionFlag)
{
    var Element = document.getElementById('nickname');
    var Elements = document.getElementById("nickspan");
    if (ActionFlag == 0)
    {
        Element.keytype = 'No';
        Elements.className = 'notetrue';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 字母、数字、特殊符号组成，长度最大 20 位。';
    }
    else
    {
        if(!RegTest(Element.value, /^[_A-Za-z0-9\u4e00-\u9fa5]{2,20}$/))
        {
            Element.keytype = 'No';
	        Elements.className = 'noteerror';
            Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 字母、数字、特殊符号组成，长度最大 20 位。';
	    }
        else
        {
            requestSimpleService = UserService.getUserNick(Element.value, OnRequestNick);
        }
    }
}

/* 验证用户昵称结果 */
function OnRequestNick(result,result1)
{
    var Element = document.getElementById('nickname');
    var Elements = document.getElementById("nickspan");
    if(result)
    {
        Element.keytype = 'No';
        Elements.className = 'noteerror';
        Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 对不起，该用户昵称已经存在。';
    }
   
    else if(result1 == true ) 
    {
        Element.keytype = 'No';
        Elements.className = 'noteerror';
        Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 对不起，此用户昵称已被系统禁止注册。'; 
    }
    
     else
    {
        Element.keytype = 'Yes';
        Elements.className = 'note';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，该用户昵称可以注册。'; 
    }
}

//用户形象
function checkShowHtml(strValue)
{
    strTime = getDataTime();
    var Element = document.getElementById('UShow');
    var Elements = document.getElementById('ListShow');
    //Element.src = 'UserShow.aspx?sex=' + strValue;
    //加上strTime,解决分页出错问题
    Element.src = 'UserShow.aspx?sex=' + strValue + '&strTime=' + strTime;
    Elements.style.display = 'block';
    checkShow("0");
}

 //获取用户形象
function getShow(strValue)
{
    parent.document.all.zaoxing.value = strValue;
} 


/* 检测密码 */
function checkPW(ActionFlag)
{
    var Element = document.getElementById('password');
    var Elements = document.getElementById("pwspan");
    if(ActionFlag == 0)
    {
        Element.keytype = 'No';
        Elements.className = 'notetrue';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 密码由6-20个英文字母或数字组成。';
    }
    else
    {
        if(!RegTest(Element.value, /^[0-9a-zA-Z]{6,20}$/))
        {
            Element.keytype = 'No';
	        Elements.className = 'noteerror';
            Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 密码由6-20个英文字母或数字组成。';
	    }
        else
        {
            Element.keytype = 'Yes';
	        Elements.className = 'note';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，密码检测通过。';
        }  
    }
}

/* 校验密码 */
function checkPWS(ActionFlag)
{
    var Element = document.getElementById('passwrods');
    var Elements = document.getElementById("pwsspan");
    var Elementss = document.getElementById('password');
    //alert(Elementss);
    
    if(Elementss.value.length < 6)
    {
        Elementss.focus();
    }
    else
    {
        if(ActionFlag == 0)
        {
            Element.keytype = 'No';
            Elements.className = 'notetrue';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 密码由6-20个英文字母或数字组成。';
        }
        else
        {
            if(Element.value != Elementss.value)
            {
                Element.keytype = 'No';
                Elements.className = 'noteerror';
                Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 两次输入密码不一至，请重新输入。';
            }
            else
            {
                Element.keytype = 'Yes';
                Elements.className = 'note';
                Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，密码检测通过。';
            }
      }
    }
        
       
}


/* 银行密码 */
function check2PW(ActionFlag)
{
    var Element = document.getElementById('pass2word');
    var Elements = document.getElementById("pws2pan");
    if(Element.value.length > 0)
    {
        if(ActionFlag == 0)
        {
            Element.keytype = 'No';
            Elements.className = 'notetrue';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 银行密码由6-20个英文字母或数字组成。';
        }
        else
        {
            if(!RegTest(Element.value, /^[0-9a-zA-Z]{6,20}$/))
            {
                Element.keytype = 'No';
                Elements.className = 'noteerror';
                Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 银行密码由6-20个英文字母或数字组成。';
            }
            else
            {
                Element.keytype = 'Yes';
                Elements.className = 'note';
                Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，银行密码检测通过。';
            }  
            
        }
     }
        else
        {
            Element.keytype = 'No';
            Elements.className = 'note';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 银行密码为选填项，可以不填写。';
        }
}


/* 校验银行密码 */
function check2PWS(ActionFlag)
{
    var Element = document.getElementById('pass2wrods'); //二次银行密码
    var Elements = document.getElementById("pws2pan2");
    var Elementss = document.getElementById('pass2word'); //第一次银行密码
    //alert(Element);
   if(Elementss.value.length > 0)
    {
//        if(Elementss.value.length < 6)
//        {
//            Elementss.focus();
//        }
//        else
//        {
//            if(ActionFlag == 0)
//            {
//                Element.keytype = 'No';
//                Elements.className = 'notetrue';
//                Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 银行密码由6-20个英文字母或数字组成。';
//            }
//            else
//            {
                if(Element.value != Elementss.value)
                {
                    Element.keytype = 'No';
	                Elements.className = 'noteerror';
                    Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 两次二级输入密码不一至，请重新输入。';
	            }
                else
                {
                    Element.keytype = 'Yes';
	                Elements.className = 'note';
                    Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，银行密码检测通过。';
                }
//            }
//        }
      }
       else
        {
            Element.keytype = 'No';
            Elements.className = 'note';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 银行密码为选填项，可以不填写。';
        }
}

/* 邮箱检测 */
function checkEmail(ActionFlag)
{
    var Element = document.getElementById('email');
    var Elements = document.getElementById("emailspan");
    if(ActionFlag == 0)
    {
        Element.keytype = 'No';
        Elements.className = 'notetrue';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 请按正确格填写电子邮箱。';
    }
    else
    {
        if(!RegTest(Element.value, /^[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}$/))
        {
            Element.keytype = 'No';
	        Elements.className = 'noteerror';
            Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 请按正确格填写电子邮箱。';
	    }
        else
        {
            requestSimpleService = UserService.getEmail(Element.value, OnRequestEmail);
        }
    }
}

/* 验证电子邮箱结果 */
function OnRequestEmail(result)
{
    var Element = document.getElementById('email');
    var Elements = document.getElementById("emailspan");
    if(result)
    {
        Element.keytype = 'No';
        Elements.className = 'noteerror';
        Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 对不起，该电子邮箱已被注册。';
    }
    else
    {
        Element.keytype = 'Yes';
        Elements.className = 'note';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，电子邮箱检测通过。'; 
    }
}

/* 检测手机 */
function checkmobile(ActionFlag)
{
    var Element = document.getElementById('mobile');
    var Elements = document.getElementById("mobilespan");
    if(ActionFlag == 0)
    {
        Element.keytype = 'No';
        Elements.className = 'notetrue';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 请按正确格填写您的手机号码，例如:13800138000。';
    }
    else
    {
        if(Element.value.length > 0)
        {
            if(!RegTest(Element.value, /^[0-9]{11}$/))
            {
                Element.keytype = 'No';
	            Elements.className = 'noteerror';
                Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 请按正确格填写您的手机号码，例如:13800138000。';
	        }
            else
            {
                Element.keytype = 'Yes';
                Elements.className = 'note';
                Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，手机号码检测通过。'; 
            }
        }
        else
        {
            Element.keytype = 'No';
            Elements.className = 'note';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 手机号码为选填项，可以不填写。';  
        }
    }
}


function checkAddress(ActionFlag)
{
    var Element = document.getElementById('Address');
    var Elements = document.getElementById("addressspan");
    if(ActionFlag == 0)
    {
        Element.keytype = 'No';
        Elements.className = 'notetrue';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/>请正确输入推荐人用户名。';
    }
    else
    {
        //        if(Element.value.length > 0)
        //        {
        //           
        //                Element.keytype = 'Yes';
        //                Elements.className = 'note';
        //                Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，推荐人输入成功。'; 
        //        }
        //        else
        //        {
        //            Element.keytype = 'No';
        //            Elements.className = 'note';
        //            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 没有推荐人，可以不填写。';  
        //        }
        if(Element.value.length > 0)
        {
           if(!RegTest(Element.value, /^[0-9a-zA-Z-_]{5,20}$/))
            {
                Element.keytype = 'No';
	            Elements.className = 'noteerror';
                Elements.innerHTML = '<img src="images/b1.gif" class="regimg"/> 推荐人名称由5-20个英文字母或数字组成。';
	        }
            else
            {
                requestSimpleService = UserService.getAddress(Element.value, OnRequestAddress);
            }
        }
        else
        {
            Element.keytype = 'No';
            Elements.className = 'note';
            Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/>推荐人为选填项，可以不填写。';
        }
    }
}

/* 验证用户名结果 */
function OnRequestAddress(result)
{
    var Element = document.getElementById('address');
    var Elements = document.getElementById("addressspan");
    if(result)
    {
        Element.keytype = 'Yes';
        Elements.className = 'note';
        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 恭喜，该推荐人存在。';
    }
      else
        {
             Element.keytype = 'Yes';
             Elements.className = 'note';
             Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/> 对不起，推荐人不存在。'; 
    //        Element.keytype = 'NO';
    //        Elements.className = 'noteerror';
    //        Elements.innerHTML = '<img src="images/b2.gif" class="regimg"/>请正确填写推荐人用户名。'; 
        }
}



 //显示隐藏

function checkShow(ActionFlag)
{
    var Element = document.getElementById('showspan');
    var Elements = document.getElementById('ListShow');
    if(ActionFlag != 0)
    {
        Element.innerHTML = '<img src="images/dx2.gif" width="206" height="19" border="0" onmouseover="this.src = \'images/dx.gif\';" onmouseout="this.src = \'images/dx2.gif\';" style="cursor: hand;" onclick="checkShow(\'0\');" />';
        Elements.style.display = 'none';
    }
    else
    {
        Element.innerHTML = '<img src="images/dxs2.gif" width="206" height="19" border="0" onmouseover="this.src = \'images/dxs.gif\';" onmouseout="this.src = \'images/dxs2.gif\';" style="cursor: hand;" onclick="checkShow(\'1\');" />';
        Elements.style.display = 'block';
    }
}
 

/* 提交检测 */
function GetPost()
{
    var EleUser = document.getElementById('username');
    if(EleUser.keytype != 'Yes')
    {
        EleUser.focus();
        return false;
    }
    var EleNick = document.getElementById('nickname');
    if(EleNick.keytype != 'Yes')
    {
        EleNick.focus();
        return false;
    }
    var ElePw = document.getElementById('password');
    if(ElePw.keytype != 'Yes')
    {
        ElePw.focus();
        return false;
    }
    var ElePwd = document.getElementById('passwrods');
    if(ElePwd.keytype != 'Yes')
    {
        ElePwd.focus();
        return false;
    }
//    var ElePwd = document.getElementById('pass2word');
//    if(ElePwd.keytype != 'Yes')
//    {
//        ElePwd.focus();
//        return false;
//    }
//     var ElePwd = document.getElementById('pass2words');
//    if(ElePwd.keytype != 'Yes')
//    {
//        ElePwd.focus();
//        return false;
//    }
    var EleEmail = document.getElementById('email');
    if(EleEmail.keytype != 'Yes')
    {
        EleEmail.focus();
        return false;
    }
     var EleIsaccept = document.getElementById('isaccept');
    if(!EleIsaccept.checked)
    {
        alert("您是否接受协议？");
        EleIsaccept.focus();
        return false;
    }
    var Element = document.getElementById('ImageButtonPost');
    Element.style.display = 'none';
    var EleMsg = document.getElementById('LoadingMsg');
    EleMsg.style.display = 'block';
    return true;

}

