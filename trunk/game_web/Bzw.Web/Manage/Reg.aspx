<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Reg" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebLeft" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/password_check.js"></script>

    <%-- <script type="text/javascript" src="/Public/Js/chkcard.js"></script>--%>

    <script type="text/javascript">
<!--
        var tguser = '<%=string.IsNullOrEmpty( BCST.Common.CommonManager.Web.Request( "recommend", "" ) ) ? "" : BCST.Common.CommonManager.Web.Request( "recommend", "" )%>';
        //init msg value
        var msgUsername = ' 用户名长度6～12个字符，由字母、数字组成。';
        var msgNickname = ' 字母、数字、特殊符号、中文组成，长度为2-12位。';
        var msgPwd2 = ' 请再输入一遍您上面输入的密码。';
        var msgEmail = ' 请填写真实，并确认是您最常用的电子邮箱。';
        var msgValidcode = ' 看不清？换一张！';
        var msgPromoter = ' 填入推荐人的用户名即可获赠<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>。';
 //-->
    </script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webtop1" runat="server" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebLeft:Control ID="webleft" runat="server" />
        </div>
        <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    注册</h3>
                <p class="dqwz">
                    当前位置：首页 > 注册</p>
            </div>
            <div id="sub_nr">
             <div class="cz">
                <p>
                    <strong class="text04">帐号信息</strong></p>
                <table width="685" summary="" border="0">
                    <caption>
                    </caption>
                    <colgroup>
                        <col width="20%" />
                        <col width="80%" />
                    </colgroup>
                    <tbody>
                        <tr>
                            <th scope="row">
                                <label for="id01">
                                    * 用户名</label>
                            </th>
                            <td>
                                <input name="username" type="text" class="in" id="username" maxlength="12" onblur="chkUserName(msgUsername)" />&nbsp;<span
                                    class="note" id="unamespan">

                                    <script type="text/jscript">                                        document.write(msgUsername);</script>

                                </span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id02">
                                    * 登录密码</label>
                            </th>
                            <td>
                                <input name="pwd" type="password" class="in" id="pwd" maxlength="20" onkeyup="checklevel(this.value)"
                                    onblur="chkPwd()" />
                                <span class="note" id="pwdspan">密码由6-20个英文字母或数字组成。</span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id03">
                                    * 密码确认</label>
                            </th>
                            <td>
                                <input name="pwd2" type="password" class="in" id="pwd2" maxlength="20" onblur="chkPwd2()" />
                                <span class="note" id="pwd2span">请再次输入您的密码，保证无误。 </span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id04">
                                    &nbsp;&nbsp;&nbsp;密码强度</label>
                            </th>
                            <td align="left" valign="middle">
                                <table border="0" cellspacing="1" class="pwSafe" style="border-top: 0px;">
                                    <tr>
                                        <td id="strength_L">
                                            弱
                                        </td>
                                        <td id="strength_M">
                                            中
                                        </td>
                                        <td id="strength_H">
                                            强
                                        </td>
                                    </tr>
                                </table>
                                <p class="text06">
                                    注：您的初始银行密码与您刚所填的密码相同,可在个人管理中心修改。</p>
                            </td>
                        </tr>
                    </tbody>
                </table>
                <p style="padding-top: 60px;">
                    <strong class="text04">个人信息</strong></p>
                <table width="685" summary="" border="0">
                    <caption>
                    </caption>
                    <colgroup>
                        <col width="20%" />
                        <col width="80%" />
                    </colgroup>
                    <tbody>
                        <tr>
                            <th scope="row">
                                <label for="id01">
                                    * 用户昵称</label>
                            </th>
                            <td>
                                <input name="nickname" type="text" class="in" id="nickname" maxlength="12" onblur="chkNickName(msgNickname)" />
                                <span class="note" id="nickspan">

                                    <script type="text/jscript">                                        document.write(msgNickname);</script>

                                </span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id02">
                                    &nbsp;&nbsp;&nbsp;联系电话</label>
                            </th>
                            <td>
                                <input name="mobile" id="mobile" type="text" class="in" maxlength="16" onblur="chkPhone()" />
                                <span class="note" id="mobilespan">为确保奖品、礼品的准确投递，请填写真实号码。</span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id03">
                                    * 身份证号</label>
                            </th>
                            <td>
                                <input name="idcard" id="idcard" type="text" class="in" maxlength="18" onblur="chkidcard()" />
                                <span class="note" id="idcardspan">请填写真实的身份证号，填写后将不可改。</span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id04">
                                    &nbsp;&nbsp;&nbsp;性&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;别</label>
                            </th>
                            <td>
                                <input type="radio" name="sex" id="sex1" value="1" checked="checked" />
                                <label for="sex1">
                                    男</label>
                                <input type="radio" name="sex" id="sex2" value="0" />
                                <label for="sex2">
                                    女</label>
                            </td>
                        </tr>
                        <%if (ConfigurationManager.AppSettings["ClothingMall"] != "1")
                          { %>
                        <tr>
                            <th scope="row">
                                <label for="id05">
                                    &nbsp;&nbsp;&nbsp;游戏头像</label>
                            </th>
                            <td style="padding: 5px 0 5px 10px;">
                                <input name="hidLogoID" id="hidLogoID" value="" type="hidden" />
                                <a href="javascript:void(0);" onclick="OnImgClick();" id="hrefImage"></a><a href="javascript:void(0);"
                                    onclick="OnImgClick();" id="hrefBtn" style="margin-left: 3px;">
                                    <img src="/images/cont_btn15.jpg" width="13" height="28" /></a>

                                <script src="/Public/js/public.js"></script>

                                <script>
                                    $("input[name=sex]").each(
																	function() {
																	    var o = $(this);
																	    o.click(
																			function() {
																			    OnSexChange(o.val());
																			}
																		);
																	}
																);
                                    //性别选择事件
                                    function OnSexChange(sex) {
                                        if (sex == "1") {
                                            $("#hrefImage").html("<img id='1' src='/Image/users/b_1.png' height='28' width='20' border='0' />");

                                        }
                                        else {
                                            $("#hrefImage").html("<img id='1' src='/Image/users/g_1.png' height='28' width='20' border='0' />");

                                        }
                                    }
                                    $("#hidLogoID").val("1");
                                    OnSexChange("1");
                                    //显示头像选择框事件
                                    function OnImgClick() {
                                        var sex = $("input[name=sex]:checked").val();
                                        var defimg = parseInt($("#hrefImage>img").attr("id"), 10);
                                        var i = 1;
                                        var prefix = "";
                                        var postfix = "</span>";
                                        var msg = "";
                                        if (sex == "1") {
                                            while (i <= 6) {
                                                if (defimg == i)
                                                    prefix = "<span style='display:inline-block;border:1px solid #333;margin:0 0 10px 8px;cursor:pointer;padding:2px;background:#ffff00;'>";
                                                else
                                                    prefix = "<span style='display:inline-block;border:1px solid #fff;margin:0 0 10px 8px;;cursor:pointer;padding:2px;'>";
                                                ////																			if(i == 3)
                                                ////																				postfix += "";
                                                ////																			else
                                                ////																				postfix = "</span>";
                                                msg += prefix + "<img id='" + i + "' src='/Image/users/b_" + i + ".png' border='0' onclick='OnImgChange(" + sex + ",this)' />" + postfix;
                                                i++;
                                            }
                                        }
                                        else {
                                            while (i <= 6) {
                                                if (defimg == i)
                                                    prefix = "<span style='display:inline-block;border:1px solid #333;margin:0 0 10px 8px;cursor:pointer;padding:2px;background:#ffff00;'>";
                                                else
                                                    prefix = "<span style='display:inline-block;border:1px solid #fff;margin:0 0 10px 8px;;cursor:pointer;padding:2px;'>";
                                                if (i == 3)
                                                    postfix += "<br />";
                                                else
                                                    postfix = "</span>";
                                                msg += prefix + "<img id='" + i + "' src='/Image/users/g_" + i + ".png' border='0' onclick='OnImgChange(" + sex + ",this)' />" + postfix;
                                                i++;
                                            }
                                        }
                                        Msg(msg, 300);
                                    }
                                    //图片选择事件
                                    function OnImgChange(sex, obj) {
                                        if (obj == null)
                                            return;
                                        $("#hidLogoID").val(obj.id);
                                        $("#hrefImage").html("<img id='" + obj.id + "' src='/Image/users/" + (sex == "1" ? "b" : "g") + "_" + obj.id + ".png' height='28' width='20' border='0' />");
                                        HiddenState('Tranning', 10);
                                        HiddenState('Mask', 10);
                                    }
                                </script>

                                &nbsp;&nbsp;&nbsp;
                            </td>
                        </tr>
                        <%} %>
                        <tr>
                            <th scope="row">
                                <label for="id05">
                                    &nbsp;&nbsp;&nbsp;推&nbsp;&nbsp;荐&nbsp;&nbsp;人</label>
                            </th>
                            <td>
                                <input name="promoter" type="text" class="in" id="promoter" maxlength="20" onblur="chkPromoter(msgPromoter)" />
                                <span class="note" id="promoterspan">

                                    <script type="text/jscript">                                        document.write(msgPromoter);</script>

                                </span>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                <label for="id05">
                                    * 验&nbsp;&nbsp;证&nbsp;&nbsp;码</label>
                            </th>
                            <td>
                                <input name="validcode" id="validcode" type="text" class="in" maxlength="4" onblur="chkValidCode(msgValidcode)" />
                                <img id="imgValidCode" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                    alt="点击换一张图片" src="/Public/Getcode.aspx" style="vertical-align: top; cursor: pointer;
                                    width: 50px; height: 16px" />
                                <span class="note" id="validcodespan">

                                    <script type="text/jscript">                                        document.write(msgValidcode);</script>

                                </span>
                            </td>
                        </tr>
                    </tbody>
                </table>
                <p class="ac" style="padding: 15px 0 10px 135px; width: 100%; float: left;">
                     <input type="checkbox" name="checkbox" value="checkbox" checked="checked" style="float:left; " id="isaccept"/>
			<font style="float:left;">已经阅读并同意
                        <a href="/Manage/Regg.aspx" target="_blank" class="link02">服务条款</a></font> 
                </p>
                <p class="cz_btn" style="padding: 0px; width: 99%; text-align: center; float: left;">
                    <input type="submit" name="btnSubmit" id="btnSubmit" runat="server" onserverclick="btnSubmit_ServerClick"
                        class="but_01" style="float: left; margin-left: 135px;" value="  " />
                    <input type="reset" name="Submit2" class="but_02" value="  " style="float: left;" />
                </p>
                <div class="clear">
                </div>
            </div> <div class="clear">
                </div>
           
        </div> <p >
                <img src="/Images/cont_img01.jpg" alt=""  /></p>
        </form>
    </div>
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooter" runat="server" />

    <script type="text/javascript">
<!--  
	//推荐人
    document.getElementById('promoter').value = tguser;
    document.getElementById('username').focus();
    
    /*===Check UserName========================*/
    function chkUserName(msg){
        var txt = document.getElementById('username');
        var tip = document.getElementById("unamespan");
        
        //valid is null--------------
        if(txt.value.trim().length==0){
          
            tip.className="note_no";
            tip.innerText = msg;
            return false;
        }
        //valid regx-----------------
        if(!/^[0-9a-zA-Z]{6,12}$/.test(txt.value)){
            tip.className="note_no";
            tip.innerText = msg;
            return false;
        }
        //valid is exsits---------------
        var urlData = '/Public/XmlHttpUser.aspx?type=regnameexist&username='+escape(txt.value);
    
        var strReturn = AjaxCall(urlData);
      
        if(strReturn=="1"){
            tip.className="note_no";
            tip.innerText='对不起，该用户名已经存在。';
            return false;
        }else if(strReturn=="0"){
            tip.innerText='恭喜您，该用户名可以注册。';
        }
        
        tip.className="note_yes";
        return true;
    }
    
    
    /*===Check NickName========================*/
    function chkNickName(msg){
        var txt = document.getElementById('nickname');
        var tip = document.getElementById("nickspan");
        
        //valid is null--------------
        if(txt.value.trim().length==0){
            tip.className="note_no";
            tip.innerText = msg;
            return false;
        }
        //valid regx----------------- /^[_A-Za-z0-9\u4e00-\u9fa5]{2,20}$/.test(txt.value)
        if(txt.value.trim().replace(/[^\x00-\xff]/g,"**").length<2 || txt.value.trim().replace(/[^\x00-\xff]/g,"**").length>16){
            tip.className="note_no";
            tip.innerText = "字符数是2-16，中文是两个字符。";
            return false;
        }
        //valid is exsits------------
        var urlData = '/Public/XmlHttpUser.aspx?type=nickexist&nickname='+escape(txt.value);
       
        var strReturn = AjaxCall(urlData);
       
        if(strReturn=="1"){
            tip.className="note_no";
            tip.innerText='对不起，该用户昵称已经存在。';
            return false;
        }else if(strReturn=="0"){
            tip.innerText='恭喜您，该用户昵称可以注册。';
        }
        
        tip.className="note_yes";
        return true;
    }
    
    /*===Check Pwd========================*/
    function chkPwd(){
        var txt = document.getElementById('pwd');
        var tip = document.getElementById("pwdspan");
        
        //valid is null--------------
        if(txt.value.trim().length==0){
            tip.className="note_no";
            return false;
        }
        //valid regx-----------------
        if(!/^[0-9a-zA-Z]{6,20}$/.test(txt.value)){
            tip.className="note_no";
            return false;
        }
        
        tip.className="note_yes";
        return true;
    }
    
    /*===Check Pwd2========================*/
    function chkPwd2(){
        var txt = document.getElementById('pwd');
        var txt2 = document.getElementById('pwd2');
        var tip = document.getElementById("pwd2span");
        
        if(txt.value.trim().length<6 || txt.value.trim().length>20 ){
            txt.focus();
            return false;
        }
        
        if(txt.value.trim()!=txt2.value.trim()){
            tip.className="note_no";
            tip.innerText='两次输入密码不一致，请重新输入。';
            return false;
        }
        
        tip.className="note_yes";
        tip.innerText='恭喜您，密码检测通过。';
        return true;
    }
    
    
    
	   
    /*===Check Phone Number========================*/
    function chkPhone(){
         var txt = document.getElementById('mobile');
         var tip = document.getElementById("mobilespan");
         if (txt.value.trim().length>0)
         {
             
             if(!/^(\(\d{3,4}\)|\d{3,4}-|\d{3})\d{7,8}$/.test(txt.value))
             {
                tip.className="note_no";
                tip.innerText='电话号码不正确！区号用()或- 隔开。';
                return false;
             }
             else
             {
                tip.className="note_yes";
                tip.innerText='恭喜您，电话号码检测通过。';
                return true;
             }
         }
         else{
			tip.className="note";
            tip.innerText = '为确保奖品、礼品的准确投递，请填写真实号码。';
            return true;
         }
    }
    

    /*===Check Email========================*/
    function chkEmail(msg){
        var txt = document.getElementById('email');
        var tip = document.getElementById("emailspan");
        
        //valid is null--------------
        if(txt.value.trim().length>0){
           
				//valid regx-----------------
				if(!/^[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}$/.test(txt.value)){
					tip.className="note_no";
					tip.innerText = '请按正确格式填写电子邮箱。';
					return false;
				}
		        
				//valid is exsits------------
				var urlData = '/Public/XmlHttpUser.aspx?type=emailexist&email='+escape(txt.value);
		 
				var strReturn = AjaxCall(urlData);
		 
				if(strReturn=="1"){
					tip.className="note_no";
					tip.innerText='对不起，该电子邮箱已被注册。';
					return false;
				}else if(strReturn=="0"){
					tip.innerText='恭喜您，电子邮箱检测通过。';
				}
  
        tip.className="note_yes";
        return true;
        }
        else
        { tip.className="note";
            tip.innerText = msg;
            
        }
    }
    
    
    /*===Check Promoter========================*/
    function chkPromoter(msg){
        var txt = document.getElementById('promoter');
        var tip = document.getElementById("promoterspan");
        
        //valid is exsits------------
        if(txt.value.trim().length>0){
            var urlData = '/Public/XmlHttpUser.aspx?type=tgnameexist&username='+escape(txt.value);
            //alert(urlData);
            var strReturn = AjaxCall(urlData);
            //alert(strReturn);
            if(strReturn=="0"){
                tip.className="note_no";
                tip.innerText='对不起，推荐人不存在。';
                return false;
            }else if(strReturn=="1"){
                tip.innerText='恭喜您，该推荐人存在。';
            }
            
            tip.className="note_yes";
        }
        else{
            tip.className="note";
            tip.innerText=msg;
        }
        
        return true;
    }
    
    
    /*===Check chkValidCode========================*/
    function chkValidCode(msg){
        var txt = document.getElementById('validcode');
        var tip = document.getElementById("validcodespan");
        
        //valid is null--------------
        if(txt.value.trim().length==0){
            tip.className="note_no";
            tip.innerText = msg;
            return false;
        }
        //valid regx-----------------
        if(!/^[0-9]{4}$/.test(txt.value)){
            tip.className="note_no";
            tip.innerText = "验证码输入错误，验证码必须为4位的数字。";
            return false;
        }
        //valid is exsits---------------
        var urlData = '/Public/XmlHttpUser.aspx?type=validcode&code='+escape(txt.value);
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        if(strReturn=="-1"){
            tip.className="note_no";
            tip.innerText='验证码已经失效，请输入新的验证码。';
            document.getElementById('imgValidCode').src='/Public/Getcode.aspx?token='+tokenKey();
            txt.value='';
            return false;
        }
        else if(strReturn=="1"){
            tip.className="note_no";
            tip.innerText='验证码输入错误，请重新输入。';
            return false;
        }else if(strReturn=="0"){
            tip.innerText='验证码输入正确。';
        }
        
        tip.className="note_yes";
        return true;
    }
 
	function chkidcard(){
		var txt = document.getElementById('idcard');
        var tip = document.getElementById("idcardspan");
        if(<%=needIDCard %>=="1"){
			 if(!idcard())
			 {
				tip.className="note_no";
				tip.innerText='身份证号无效！';
				return false;
			 }
			 else
			 {
			    //判断是否做了身份证注册个数限制
			    var urlData = '/Public/XmlHttpUser.aspx?type=cardnovalid&cardno='+escape(txt.value);
			      var strReturn = AjaxCall(urlData);
			      
			      if(strReturn=="0")
			      {
			        tip.className="note_no";
				    tip.innerText='同一身份证号注册次数过多！';
				    return false;
			      }
			    //成年人验证
			 		 if(<%=needProcted %>=="1"){
				        var vl=txt.value;
			        	var birth;
			        	if(vl.length==15){
			        	birth="19"+vl.substr(6,6);
			        	}
			        	else{
				         birth=vl.substr(6,8);	
				        }
				        if(chkIsAdults(birth)==-1) 
		                {
		                tip.className="note_no";
			        	tip.innerText='对不起，您还未成年！';
			        	return false;	
			        	}
	    	 
				    } 
				tip.className="note_yes";
				tip.innerText='恭喜您，身份证号码检测通过。';
				return true;
			  }
        }
        else
        {
			if(txt.value.trim().length>0)
			{
				if(!idcard())
				{
					tip.className="note_no";
					tip.innerText='身份证号码无效！';
					return false;
				}
				else
				{
					tip.className="note_yes";
					tip.innerText='恭喜您，身份证号码检测通过。';
					return true;
				}
			}
			else{
				tip.className="note";
				tip.innerText='请填写真实的身份证号，填写后将不可改。';
				return true;
			}
        }
        
	}   
/*---------------验证身份证是否合法------------------*/
function idcard(){
	var vl=document.getElementById("idcard").value;
	var tst=/^\d{18}$|^\d{17}(\d|x|X)$|^\d{15}$/;	
	if(!tst.test(vl)){		//验证是否为18位数字或17为数字+X或15位数字	
		return false;
	}
	if(vl.length==15){			
		var address = "11x22x35x44x53x12x23x36x45x54x13x31x37x46x61x14x32x41x50x62x15x33x42x51x63x21x34x43x52x64x65x71x81x82x91";
		var sf=vl.substring(0,2);
		if(address.indexOf(sf)==-1){	//省份验证
			//alert("地址错误");
			return false;
		}
		var birth="19"+vl.substr(6,6);
		var year=parseInt("19"+vl.substr(6,2),10);
		var month=vl.substr(8,2);
		var day=vl.substr(10,2);
		if(chkdate(birth,year,month,day)==-1){	//生日的验证
			return false;
		}	
		return true;	
	}
	if(vl.length==18){
		var address = "11x22x35x44x53x12x23x36x45x54x13x31x37x46x61x14x32x41x50x62x15x33x42x51x63x21x34x43x52x64x65x71x81x82x91"; //省份验证
		var sf=vl.substring(0,2);			
		if(address.indexOf(sf)==-1){
			//alert("地址错误");
			return false;
		}
		var birth=vl.substr(6,8);	
		var year=parseInt(vl.substr(6,4),10);
		var month=vl.substr(10,2);
		var day=vl.substr(12,2);
		if((parseInt(year,10)>2010)||(parseInt(year,10)<1900)){ //年份范围验证
			//alert("年份错误");
			return false;
		}
		if(chkdate(birth,year,month,day)==-1){	 //生日的验证
			return false;
		}
		var rightcode=new Array("1","0","X","9","8","7","6","5","4","3","2"); //有效校正码
		var heft= new Array("7","9","10","5","8","4","2","1","6","3","7","9","10","5","8","4","2"); //身份证前17位每位占有权重
		var cardarr=vl.substr(0,17).split("");
		var sum=0;
		for(var i=0;i<17;i++){
			sum+=parseInt(cardarr[i],10)*parseInt(heft[i],10);
		}
		sum=sum%11;
		if(rightcode[sum].toUpperCase()!=vl.substr(17).toUpperCase()){
			//alert("校正码错误");
			return false;
		}
	}
	//alert("恭喜您,测试通过");
	return true;
}


/*---------------验证身份证中的生日是否合法------------------*/
function chkdate(birth,year,month,day){
	var bigmonth="01x03x05x07x08x10x12";
	var smallmonth="02x04x06x09x11";
	if((parseInt(month,10)>12)||(parseInt(month,10)<1)){	//验证月份是否合法
		//alert("月份错误");
		return -1;
	}
	/*判断日期是否合法*/
	if(bigmonth.indexOf(month)!=-1){			//月份是大月时
		if(day>31||day<1){
			//alert("日期错误,月大");
			return -1;
		}
	}
	if(smallmonth.indexOf(month)!=-1){			//当月份是小月时
		if(day>30||day<1){
			//alert("日期错误，月小"+day);
			return -1;
		}
	}
	if(month=="02"){							//当月份是2月时
		if((year%4==0&&year%100!=0)||year%400==0){
			if(day>28||day<1){
				//alert("日期错误，二月");
				return -1;
			}
		}else{
			if(day>29||day<1){
					//alert("日期错误，二月平年");
					return -1;
			}
		}
	}
}
/*-------------验证是否大于18岁---------------*/
function chkIsAdults(age)
{
var  nowdate;
var t=new Date();  
    nowdate=parseInt(t.getFullYear()+""+((t.getMonth()+1)<10?'0'+(t.getMonth()+1):(t.getMonth()+1))+""+((t.getDate()<10?"0"+t.getDate():t.getDate())));
     if(nowdate-age<180000){//判断是否成年  
                    return -1;
                }else{  
                    return 0; //检测ID的校验位  
                }  
}
    
    function onFormSubmit(f){
    
        if(!chkUserName(msgUsername)){
            document.getElementById('username').focus();
            return false;
        }
         
        if(!chkPwd()){
            document.getElementById('pwd').focus();
            return false;
        }
          
        if(!chkPwd2()){
            document.getElementById('pwd2').focus();
            return false;
        }
    
        if(!chkNickName(msgNickname)){
            document.getElementById('nickname').focus();
            return false;
        }
        
   
       
 
         if(!chkPhone()){
            document.getElementById('mobile').focus();
            return false;
        }
        
         if(!chkidcard()){
            document.getElementById('idcard').focus();
            return false;
        }
        
  
        
        if(!chkPromoter(msgPromoter)){
            document.getElementById('promoter').focus();
            return false;
        }
        
        if(!chkValidCode(msgValidcode)){
            document.getElementById('validcode').focus();
            return false;
        }

        
        var isaccept = document.getElementById('isaccept');
        if(!isaccept.checked)
        {
            alert("您是否接受服务条款？");
            isaccept.focus();
            return false;
        }
         
        
        return true;
    }
 //-->
    </script>

</body>
</html>
