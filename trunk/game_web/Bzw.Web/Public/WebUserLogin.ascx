<%@ Control Language="C#" ClassName="WebUserLogin" %>
<span id="spanLoginForm">
<div id="login">
	<div id="login_body">
		<img src="/images/mem_login.gif" width="135" height="35" class="memImg" />
		<ul>
			<li>
				<input type="text" name="loginAccount" id="loginAccount"  />
			</li>
			<li>
				<input type="password" name="loginPwd" id="loginPwd" />
				<input type="text" name="showpw" id="showpw"/>
			</li>
			<script type="text/javascript" src="/Public/Js/jquery.js"></script>
			<script >
				var un=$("#loginAccount");				
				var pkey="请输入用户名";
				un.val(pkey);
				un.css("color","gray");
				un.focus(
					function(){
							if(un.val().trim()==pkey){
								un.val("");
								un.css("color","black");
							}
						}
					);
				un.blur(
					function(){
							if(un.val().trim()==""){
								un.val(pkey);
								un.css("color","gray");
							}
						}
					);
				//处理密码框的显示
				var lpw = $("#loginPwd");
				var spw = $("#showpw");
				lpw.css("display","none");
				spw.val("请输入密码");
				spw.css("color","gray");
				spw.focus(
					function(){
						spw.css("display","none");
						lpw.css("display","block");
						lpw.focus();
						lpw.val("");
					}						
				);
				lpw.blur(
					function(){
						if(lpw.val().trim()==""){
							lpw.css("display","none");
							spw.css({display:"block",color:"gray"});
						}
					}
				);
			</script>
		</ul>
		<div id="btn_login">
			<%--<input type="image" name="imageField" id="imageField" src="/images/btnLogin.gif" onclick="javascript:window.location.href='memCemter.html'" />--%>
			<input type="image" onclick="return CheckLogin();" name="imageField" id="imageField" src="/images/btnLogin.gif" />
		</div>
		<div id="regAndpw">
			<a href="/Manage/Reg.aspx" class="btn02 textIndent">新用户注册</a><a href="/Manage/GetPass.aspx">找回密码</a></div>
	</div>
</div>
</span>

<script type="text/javascript">

    LogSuccess();
    
    function CheckLogin(){

       if(navigator["cookieEnabled"]==false)
       {
          alert("温馨提示：\n\n对不起，登录操作需要先开启您浏览器的Cookies才能正常登录！");
       }
        
        var username = document.getElementById('loginAccount');
        if(!alertNull(username,'请输入用户名！')){
            return false;
        }
        if ( username.value=="请输入用户名"){
			alert("请输入用户名！");
			return false;
        }
        
        var pass = document.getElementById('loginPwd');
        /*if(!alertNull(pass,'请输入登录密码！')){
            return false;
        }*/
        if (pass.value==""){
			alert("请输入登录密码！");
			return false;
        }
        
        var urlData = '/Public/AjaxLogin.aspx?username='+escape(username.value);
        urlData+='&password='+escape(pass.value);
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        
        if(strReturn=="True")
        {
             //alert('登录成功！');
             LogSuccess();
          }
         else if(strReturn=="NoReg" || strReturn=="False")
          { 
               alert('温馨提示:您输入的用户名或密码错误！');
               username.focus();
               return false;
           }
         else if(strReturn=="NoPass")
          {
                alert('温馨提示:您的帐号已经被管理员限制，不能登录！');
                username.focus();
                return false;
          }
          else
           {
                alert('温馨提示:对不起，访问服务器出错，请稍候再试！！');
                username.focus();
                return false;
           }
        
        return false;
    }
    
    //显示登录成功后的面板
    function LogSuccess(){
        var urlData = '/Public/LogSuccess.aspx?tdate='+getDataTime();
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        if(strReturn!=''){
            document.getElementById('spanLoginForm').innerHTML = strReturn;
        }
    }
    
     //时间函数
    function getDataTime(){
    
	    var strDate,strTime;
	    strDate = new Date();
	    strTime = strDate.getTime();
	    return strTime;
    }
</script>

<%--<div class="login">
	<table width="250" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			td height="205">
				&nbsp;</td>
			<td height="205" valign="middle" align="right">
				<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" style="margin-left: 75px; margin-bottom: 10px" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,19,0" width="184" height="93">
					<param name="movie" value="http://game.0439.com/images/lgt.swf" />
					<param name="wmode" value="transparent">
					<param name="quality" value="high" />
					<embed src="http://game.0439.com/images/lgt.swf" quality="high" pluginspage="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" width="184" height="93"></embed>
				</object>
			</td>
		</tr>
		<tr>
			<td id="l_login">
				<table width="250" border="0" cellpadding="0" cellspacing="0" class="loginForm">
					<tr>
						<th>
							用户名：</th>
						<td>
							<input name="loginAccount" type="text" id="loginAccount" onkeypress="var key=window.event?event.keyCode:event.which;if(key==13)return CheckLogin();" /></td>
						<td rowspan="2" valign="top">
							<img src="/images/input_btn.jpg" style="cursor: pointer;" width="50" height="50" onclick="return CheckLogin();" /></td>
					</tr>
					<tr>
						<th>
							密码：</th>
						<td>
							<input name="loginPwd" type="password" id="loginPwd" onkeypress="var key=window.event?event.keyCode:event.which;if(key==13)return CheckLogin();" /></td>
					</tr>
					<tr>
						<th>
							验证码：</th>
						<td>
							<input name="loginVali" type="text" id="loginVali" maxlength="4" style="ime-mode: disabled;" onkeypress="var key=window.event?event.keyCode:event.which;if(key==13)return CheckLogin();" /></td>
						<td>
							<img src="/Public/Getcode.aspx" height="18" alt="验证码,看不清楚?请点击刷新验证码" onclick="this.src='/Public/Getcode.aspx?x=' + Math.random()" style="cursor: pointer;" id="imgVali" /></td>
					</tr>
					<tr>
						<th>
							&nbsp;</th>
						<td>
							<a href="/Manage/Reg.aspx" title="用户注册">用户注册</a>
							<a href="/Manage/GetPass.aspx" title="找回密码">忘记密码？</a></td>
						<td>
							&nbsp;</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
</div>--%>
<%--<script  src="/Public/Js/bm.js"></script>--%>
<%--<script type="text/javascript">

    LogSuccess();
    
    function CheckLogin(){

       if(navigator["cookieEnabled"]==false)
       {
          alert("温馨提示：\n\n对不起，登录操作需要先开启您浏览器的Cookies才能正常登录！");
       }
        
        var username = document.getElementById('loginAccount');
        if(!alertNull(username,'请输入用户名！')){
            return false;
        }
        
        var pass = document.getElementById('loginPwd');
        if(!alertNull(pass,'请输入登录密码！')){
            return false;
        }
        
        var vali = document.getElementById('loginVali');
        if(!alertNull(vali,'请输入验证码！')){
            return false;
        }
        
        
       // var hidpass = hex_sha1(document.getElementById("loginPwd").value);
        var urlData = '/Public/AjaxLogin.aspx?position=index&username='+escape(username.value);
        urlData+='&password='+ escape(pass.value) ;//hidpass;
        urlData+='&vali=' + vali.value;
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        
        if(strReturn=="True")
        {
             //alert('登录成功！');
             LogSuccess();
          }
         else if(strReturn=="NoReg" || strReturn=="False")
          { 
               alert('温馨提示:您输入的用户名或密码错误！');
               username.focus();
               return false;
           }
         else if(strReturn=="NoPass")
          {
                alert('温馨提示:您的帐号已经被管理员限制，不能登录！');
                username.focus();
                return false;
          }
          else if(strReturn == "ValiError")
          {
			alert("温馨提示:您输入的验证码有误，请重新输入！");
			document.getElementById("imgVali").src = "/Public/Getcode.aspx?x=" + Math.random();
			vali.value = "";
			vali.focus();
			return false;
          }
          else if(strReturn == "ValidateExpair")
          {
			alert("温馨提示:验证码已过期，请重新输入。");
			document.getElementById("imgVali").src = "/Public/Getcode.aspx?x=" + Math.random();
			vali.value = "";
			vali.focus();
			return false;
          }
          else
           {
                alert('温馨提示:对不起，服务器繁忙，请稍候重试！！');
                //alert(strReturn);
                username.focus();
                return false;
           }
        
        return false;
    }
    
    //显示登录成功后的面板
    function LogSuccess(){
        var urlData = '/Public/LogSuccess.aspx?position=index&tdate='+getDataTime();
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        if(strReturn!=''){
            document.getElementById('l_login').innerHTML = strReturn;
        }
    }
    
     //时间函数
    function getDataTime(){
    
	    var strDate,strTime;
	    strDate = new Date();
	    strTime = strDate.getTime();
	    return strTime;
    }
</script>--%>
