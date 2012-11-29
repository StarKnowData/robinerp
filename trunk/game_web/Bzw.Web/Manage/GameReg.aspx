<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GameReg"  %>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		
	</title>
	
	<link href="/style/gameRegpage.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/Global.js"></script>

	<script type="text/javascript" src="/Public/Js/password_check.js"></script>

	<script type="text/javascript">
<!--
	    var tguser = '<%=string.IsNullOrEmpty( BCST.Common.CommonManager.Web.Request( "recommend", "" ) ) ? "" : BCST.Common.CommonManager.Web.Request( "recommend", "" )%>';
	    //init msg value
	    var msgUsername = '用户名长度6～12个字符，由字母、数字组成。';
	    var msgNickname = '字母、数字、特殊符号组成，长度为2-12位。';
	    var msgPwd2 = '请再输入一遍您上面输入的密码。';
	    var msgEmail = '请填写真实，并确认是您最常用的电子邮箱。';
	    var msgValidcode = '看不清？换一张！';
	    var msgPromoter = '填入推荐人的用户名即可获赠<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>。'
 //-->
	</script>

	<script type="text/javascript">
	    document.oncontextmenu = function() { return false; };
	</script>
	<style type="text/css">
	 *{margin:0px;padding:0;}
	 body{ background-color:#edf6ff; width:500px; margin-top:5px;}
	 input{ border:1px solid #0f5d9c; width:123px;}
	 td{ height:20px;}
	</style>

</head>
<body >
	<table width="500px" border="0" cellpadding="0" cellspacing="0" >
		<tr>
			<td>
				<form id="form1" runat="server" onsubmit="return onFormSubmit(this);">
					<table width="480" border="0" cellpadding="0" cellspacing="0">
						<tr>
							<td colspan="3" width="100%">
								<asp:Label ID="Label1" runat="server" Font-Bold="True" Font-Italic="False" ForeColor="Red"
									Visible="False"></asp:Label></td>
						</tr>
						<tr>
							<td style="width:15%; text-align:right;">
								用&nbsp;户&nbsp;名：</td>
							<td style="width:28%; text-align:left;">
								<input name="username" type="text" class="input" id="username" maxlength="12" onblur="chkUserName(msgUsername)" />
								</td><td  style="width:57%; text-align:left;">
								<span class="red">*</span>
								<span class="note" id="unamespan"><script type="text/jscript">								                                      document.write(msgUsername);</script>

								</span>
							</td>
						</tr>
						<tr>
							<td style=" text-align:right;">
								登录密码：</td>
							<td>
								<input name="pwd" type="password" class="input" id="pwd" maxlength="20"  
									onblur="chkPwd()" /></td><td>
								<span class="red">*</span><span class="note" id="pwdspan"> 密码由6-20个英文字母或数字组成。</span>
							</td>
						</tr>
						<tr>
							<td style=" text-align:right;">
								确认密码：</td>
							<td>
								<input name="pwd2" type="password" class="input" id="pwd2" maxlength="20" onblur="chkPwd2()" /></td><td>
								<span class="red">*</span><span class="note" id="pwd2span"> 请再次输入您的密码，保证无误。</span>
							</td>
						</tr>
					  
					</table>
                        <table style="background-image:url(/images/gregb.png); background-repeat:no-repeat; " width="480px">
                        <tr style=" height:10px;"><td colspan="3"></td></tr>
                       	<tr>
							<td style="width:14%; text-align:right;">
								 用户昵称：</td>
							<td style="width:24%; text-align:left;">
								<input name="nickname" type="text" class="input" id="nickname" maxlength="12" onblur="chkNickName(msgNickname)" /></td>
								<td style="width:53%; text-align:left;">
								<span class="red">*</span>
								<span class="note" id="nickspan"><script type="text/jscript">								                                     document.write(msgNickname);</script>

								</span>
							</td>
							
						</tr>
						<tr>
							<td  style=" text-align:right;">
								联系电话：</td>
							<td>
								<input name="mobile" id="mobile" type="text" class="input" maxlength="16" onblur="chkPhone()" /></td><td>
								 <span class="note" id="mobilespan">为确保奖品、礼品的准确投递，请填写真实号码。</span>
							</td>
						</tr>
							<tr>
										<td align="right" valign="middle">
											身份证号：
										</td>
										<td align="left" valign="middle">
											<input name="idcard" id="idcard" type="text" class="btn5" maxlength="18" onblur="chkidcard()" /></td><td>
										 <% if(needIDCard=="1"){%><span class="red">*</span><%} %>
											<span class="note" id="idcardspan">请填写真实的身份证号，填写后将不可改。</span>
										</td>
									</tr>
						<tr>
							<td  style=" text-align:right;">
								推荐人：</td>
							<td>
								<input name="promoter" type="text" class="input" id="promoter" maxlength="20" onblur="chkPromoter(msgPromoter)" /></td><td>
								<span class="note" id="promoterspan">

									<script type="text/jscript">									    document.write(msgPromoter);</script>

								</span>
							</td>
						</tr>
						<tr>
							<td  style=" text-align:right;">
								性别：</td>
							<td colspan="2">
								<table border="0" cellpadding="0" cellspacing="0" height="30" width="100%">
									<tbody>
										<tr>
											<td align="left" valign="middle" width="35%">
												<input type="radio" name="sex" id="sex1" value="1" checked="checked"  style="width:30px;" />
												<label for="sex1">
													男</label>
												<input type="radio" name="sex" id="sex2" value="0"style="width:30px;"  />
												<label for="sex2">
													女</label>
											</td>
											 <%if (ConfigurationManager.AppSettings["ClothingMall"] != "1")
              { %>
											<td align="left" valign="middle" width="15%"  >
												游戏头像：</td>
											<td valign="middle" width="50%" >
															<input name="hidLogoID" id="hidLogoID" value="" type="hidden" />
															<a href="javascript:void(0);" onclick="OnImgClick();" id="hrefImage"></a>
															<a href="javascript:void(0);" onclick="OnImgClick();" id="hrefBtn" style="margin-left:3px;">
																<img src="/images/btn05.gif" width="13" height="28" border="0" /></a>

															<script src="/Public/js/jquery.js"></script>

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

														</td><%} %>
										</tr>
									</tbody>
								</table>
							</td>
						</tr>
						<tr>
						<td  style=" text-align:right;">个性签名：</td>
						<td colspan="2"> <textarea  rows="1"  id="sign" name="sign" cols="2" style=" width:300px;  height:78px; border:1px solid #0f5d9c;  overflow:hidden; " onkeyup="checkSign()"></textarea></td> 
						</tr>
						<tr>
							<td  style=" text-align:right;">
								验证码：</td>
							<td>
								<input name="validcode" id="validcode" type="text" class="inputa" maxlength="4" onblur="chkValidCode(msgValidcode)" /></td><td><span class="red">*</span><img
									id="imgValidCode" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
									alt="点击换一张图片" src="/Public/Getcode.aspx" style="vertical-align: top; cursor: pointer;
									width: 50px; height: 16px" />
								<span class="note" id="validcodespan">

									<script type="text/jscript">									    document.write(msgValidcode);</script>

								</span>
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;</td>
							<td  colspan="2"  >
								<input type="checkbox" name="isaccept" id="isaccept" checked="checked" style="width:20px" />已经阅读并同意<a href="/Manage/Regg.aspx"
									class="red" target="_blank">服务条款</a>
							</td> 
						 </tr>
						<tr>
							 <td></td>
							<td > 
								<input type="submit" name="btnSubmit" id="btnSubmit"  runat="server"  onserverclick="btnSubmit_ServerClick"
									class="submit" value="确定提交"  /></td>
<td>							 <input type="reset" name="Submit2" class="reset" value="" /></td> 
						</tr>
                        </table>
                        
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
            //txt.focus();死循环
            tip.className="note_no";
            tip.innerText = msg;
            return false;
        }
        //valid regx-----------------
        if(!/^[0-9a-zA-Z]{5,20}$/.test(txt.value)){
            tip.className="note_no";
            tip.innerText = msg;
            return false;
        }
        //valid is exsits---------------
        var urlData = '/Public/XmlHttpUser.aspx?type=regnameexist&username='+escape(txt.value);
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
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
                   //  tip.innerText = msg;
tip.innerText="字符数是2-16，中文是两个字符。";
            return false;
        }
        //valid is exsits------------
        var urlData = '/Public/XmlHttpUser.aspx?type=nickexist&nickname='+escape(txt.value);
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
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
//            tip.className="note_no";
//            tip.innerText='请填写您的电话号码，以便联系。';
//            document.getElementById('mobile').value='';
//            return false;
//         }

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
         }else{
			tip.className="note";
            tip.innerText = '为确保奖品、礼品的准确投递，请填写真实号码。';
            return true;
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
/*---------验证个性签名字数--------*/
function checkSign() { 
var t1=document.getElementById("sign");
var regC = /[^ -~]+/g; 
var regE = /\D+/g; 
var str = t1.value; 

if (regC.test(str)){ 
    t1.value = t1.value.substr(0,50); 
} 

if(regE.test(str)){ 
    t1.value = t1.value.substr(0,100); 
} 
}

/*---------------验证身份证中的生日是否合法------------------*/
function chkdate(birth,year,month,day){
	var bigmonth="01x03x05x07x08x10x12";
	var smallmonth="02x04x06x09x11";	
	if((parseInt(month,10))>12||(parseInt(month,10)<1)){	//验证月份是否合法
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
			//alert("日期错误，月小");
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

				</form>
			</td>
		</tr>
	</table>
</body>
</html>
