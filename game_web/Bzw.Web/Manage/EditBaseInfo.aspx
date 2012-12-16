<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_EditBaseInfo" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

    <script type="text/javascript" src="/Public/Js/password_check.js"></script>

    <script type="text/javascript" src="/Public/Js/District.js"></script>

    <style type="text/css">
        #img1, #img2, #img3, #img4, #img5
        {
            margin-right: 3px;
        }
    </style>
</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    修改资料</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 修改资料</p>
            </div>
            <div id="sub_nr">
                <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
                <div class="cz">
                    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="6" class="tab03">
                        <tbody>
                            <tr>
                                <td width="14%" height="30" align="right" valign="middle">
                                    用户名：
                                </td>
                                <td align="left" valign="middle" width="78%">
                                    <%=UiCommon.UserLoginInfo.UserName %>
                                </td>
                            </tr>
                            <tr>
                                <td align="right" height="30" valign="middle">
                                    旧密码：
                                </td>
                                <td align="left" valign="middle">
                                    <asp:TextBox ID="txtPassword" runat="server" CssClass="btn5" TextMode="Password"
                                        MaxLength="20"></asp:TextBox>
                                    <span class="red">*</span>
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    修改密码：
                                </td>
                                <td align="left" valign="middle">
                                    <%--<input name="UserPass" id="UserPass" class="btn5" onkeyup="checklevel(this.value)"
												onblur="checklevel(this.value)" type="password" />--%>
                                    <input name="pwd" type="password" class="btn5" id="pwd" onkeyup="checklevel(this.value)"
                                        maxlength="20" />
                                    <span class="red"></span><span class="note">不修改则为空，密码由6-20个英文字母或数字组成。</span>
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    密码确认：
                                </td>
                                <td align="left" valign="middle">
                                    <%--<input name="AgainPass" id="AgainPass" class="btn5" type="password" />--%>
                                    <input name="pwd2" type="password" class="btn5" id="pwd2" maxlength="20" />
                                    <span class="red"></span>请再次输入您的密码，保证无误。
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    密码强度：
                                </td>
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
                                </td>
                            </tr>
                            <tr>
                                <td width="14%" height="30" align="right" valign="middle">
                                    用户昵称：
                                </td>
                                <td align="left" valign="middle" width="78%">
                                    <input name="nickname" type="text" id="nickname" maxlength="12" class="btn5" value="<%=NickName %>"
                                        readonly="readonly" />
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    性 &nbsp;&nbsp;&nbsp;别：
                                </td>
                                <td align="left" valign="middle">
                                    <table border="0" cellpadding="0" cellspacing="0" height="30" width="100%" style="border-top: 0px;">
                                        <tbody>
                                            <tr>
                                                <td align="left" valign="middle" width="35%">
                                                    <input type="radio" name="sex" id="sex1" value="1" <%= (Sex==1 ? "checked" : "")%> />
                                                    <label for="sex1">
                                                        男</label>
                                                    <input type="radio" name="sex" id="sex2" value="0" <%= (Sex==0 ? "checked" : "")%> />
                                                    <label for="sex2">
                                                        女</label>
                                                </td>
                                                  <input name="hidLogoID" id="hidLogoID" value="" type="hidden" />
                                                <%if (ConfigurationManager.AppSettings["ClothingMall"] != "1")
                                                  { %>
                                                <td align="left" valign="middle" width="15%">
                                                    游戏头像：
                                                </td>
                                                <td valign="middle" width="50%">
                                                  
                                                    <a href="javascript:void(0);" onclick="OnImgClick();" id="hrefImage">
                                                        <%--<img src="images/1.gif" id="DefaultFace" border="0" height="30" width="30" />--%>
                                                    </a><a href="javascript:void(0);" onclick="OnImgClick();" id="hrefBtn">
                                                        <img src="/images/btn05.gif" width="13" height="28" /></a>

                                                    <script>
															$("input[name=sex]").each(
																function (){
																	var o =$(this);
																	o.click(
																		function(){
																			OnSexChange(o.val());
																		}
																	);
																}
																
															);
															//性别选择事件
															function OnSexChange(sex){
																var logoid= parseInt($("#hidLogoID").val(),10);
																if (logoid > 255){
																	$("#hrefImage").html("<img id='ImgCust' src='<%=CustImgDir %>' height='30' width='30' border='0' />");
																	$("#hidLogoID").val("<%=LogoID %>");
																}
																else{
																	if (sex=="1"){
																		$("#hrefImage").html("<img id='"+<%=LogoID %>+"' src='/Image/users/b_"+"<%=LogoID %>"+".png' height='30' width='30' border='0' />");
																		
																	}
																	else{
																		$("#hrefImage").html("<img id='"+<%=LogoID %>+"' src='/Image/users/g_"+"<%=LogoID %>"+".png' height='30' width='30' border='0' />");
																		
																	}
																}
															}
															$("#hidLogoID").val("<%=LogoID %>");
															OnSexChange("<%=Sex %>");
															//显示头像选择框事件
																function OnImgClick()
																{
																	var sex = $("input[name=sex]:checked").val();
																	var defimg = parseInt( $("#hrefImage>img").attr("id"),10);
																	var i=1;
																	var prefix = "";
																	var postfix = "</span>";
																	var msg = "";
																	if(sex == "1")
																	{
																		while(i<=6)
																		{
																			if(defimg == i)
																				prefix = "<span style='display:inline-block;border:1px solid blue;margin-left:10px;margin-bottom:10px;cursor:pointer;padding:2px;'>";
																			else
																				prefix = "<span style='display:inline-block;border:1px solid Transparent;margin-left:8px;margin-bottom:10px;cursor:pointer;padding:2px;'>";
																			if(i == 3)
																				postfix += "<br />";
																			else
																				postfix = "</span>";
																			msg += prefix + "<img id='"+i+"' src='/Image/users/b_"+i+".png' border='0' onclick='OnImgChange("+sex+",this)' />" + postfix;
																			i++;
																		}
																	}
																	else
																	{
																		while(i<=6)
																		{
																			if(defimg == i)
																				prefix = "<span style='display:inline-block;border:1px solid blue;margin-left:10px;margin-bottom:10px;cursor:pointer;padding:2px;'>";
																			else
																				prefix = "<span style='display:inline-block;border:1px solid Transparent;margin-left:8px;margin-bottom:10px;cursor:pointer;padding:2px;'>";
																			if(i == 3)
																				postfix += "<br />";
																			else
																				postfix = "</span>";
																			msg += prefix + "<img id='"+i+"' src='/Image/users/g_"+i+".png' border='0' onclick='OnImgChange("+sex+",this)' />" + postfix;
																			i++;
																		}																		
																	}
																	Msg(msg,300);
																}
																//图片选择事件
																function OnImgChange(sex,obj)
																{
																	if(obj == null)
																		return;
																	$("#hidLogoID").val(obj.id);
																	$("#hrefImage").html("<img id='"+obj.id+"' src='/Image/users/"+(sex == "1" ? "b" : "g")+"_"+obj.id+".png' height='30' width='30' border='0' />");
																	HiddenState('Tranning',10);
																	HiddenState('Mask',10);
																}
															
															
                                                    </script>

                                                </td>
                                                <%} %>
                                            </tr>
                                        </tbody>
                                    </table>
                                </td>
                            </tr>
                            <tr>
                                <td style="height: 30px; text-align: center;">
                                    职业：
                                </td>
                                <td>
                                    <select name="txtOccuPation" id="txtOccuPation">
                                        <option value="自由职业者">自由职业者</option>
                                        <option value="在校学生">在校学生</option>
                                        <option value="计算机·网络·技">计算机·网络·技术</option>
                                        <option value="经营管理">经营管理</option>
                                        <option value="文体工作">文体工作</option>
                                        <option value="销售">销售</option>
                                        <option value="医疗卫生">医疗卫生</option>
                                        <option value="农林牧渔劳动者">农林牧渔劳动者</option>
                                        <option value="美术·设计·创意">美术·设计·创意</option>
                                        <option value="电子·电器·通信技术">电子·电器·通信技术</option>
                                        <option value="外出务工人员">外出务工人员</option>
                                        <option value="贸易·物流·采购·运输">贸易·物流·采购·运输</option>
                                        <option value="财务·审计·统计">财务·审计·统计</option>
                                        <option value="电气·能源·动力">电气·能源·动力</option>
                                        <option value="个体经营·商业零售">个体经营·商业零售</option>
                                        <option value="军人警察">军人警察</option>
                                        <option value="美容保健">美容保健</option>
                                        <option value="行政·后勤">行政·后勤</option>
                                        <option value="教育·培训">教育·培训</option>
                                        <option value="技工">技工</option>
                                        <option value="工厂生产">工厂生产</option>
                                        <option value="宗教、神职人员">宗教、神职人员</option>
                                        <option value="工程师">工程师</option>
                                        <option value="新闻出版·文化工作">新闻出版·文化工作</option>
                                        <option value="金融">金融</option>
                                        <option value="人力资源">人力资源</option>
                                        <option value="保险">保险</option>
                                        <option value="法律">法律</option>
                                        <option value="翻译">翻译</option>
                                        <option value="待业/无业/失业">待业/无业/失业</option>
                                        <option value="市场·公关·咨询·媒介">市场·公关·咨询·媒介</option>
                                        <option value="酒店·餐饮·旅游·其他服务">酒店·餐饮·旅游·其他服务</option>
                                        <option value="党政机关事业单位工作者·公务员类">党政机关事业单位工作者·公务员类</option>
                                        <option value="建筑·房地产·装饰装修·物业管理">建筑·房地产·装饰装修·物业管理</option>
                                        <option value="其他">其他</option>
                                    </select>
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    所在地：
                                </td>
                                <td align="left" valign="middle">
                                    <select name="province" id="province">
                                    </select>
                                    <select name="city" id="city">
                                    </select>
                                    <span class="red"></span>
                                    <input type="hidden" id="hidProvince" name="hidProvince" value="<%= province%>" />
                                    <input type="hidden" id="hidCity" name="hidCity" value="<%= city%>" />
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    详细地址：
                                </td>
                                <td>
                                    <input type="text" id="txtAddress" name="txtAddress" class="btn5" value="<%= address%>" />
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    电子邮箱：
                                </td>
                                <td align="left" valign="middle">
                                    <%--<input name="Email" id="Email" class="btn5" type="text" />--%>
                                    <input name="email" type="text" class="btn5" id="email" value="<%=Email %>" maxlength="40" />
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    QQ：
                                </td>
                                <td align="left" valign="middle">
                                    <%--<input name="Email" id="Email" class="btn5" type="text" />--%>
                                    <input name="qqnum" type="text" class="btn5" id="qqnum" value="<%=qqNum%>" maxlength="40" />
                                </td>
                            </tr>
                            <tr>
                                <td height="30" align="right" valign="middle">
                                    手机号码：
                                </td>
                                <td align="left" valign="middle">
                                    <%--<input name="Handset" id="Handset" class="btn5" type="text" />--%>
                                    <input name="mobile" id="mobile" type="text" class="btn5" maxlength="20" value="<%=Phone %>" />
                                </td>
                            </tr>
                            <tr>
                                <td height="60" scope="row">
                                    &nbsp;
                                </td>
                                <td valign="middle">
                                    <input type="submit" class="but_01" name="button5" id="Submit1" value="  " onserverclick="button5_ServerClick"
                                        runat="server" />
                                </td>
                            </tr>
                        </tbody>
                        <%--
									<input name="visitant" id="visitant" class="btn324" size="20" value="" type="hidden" />
									<tr height="30">
										<td height="30" align="right" valign="middle">
											验证码：</td>
										<td align="left" valign="middle">
											<input name="RegValidCode2" size="8" id="RegValidCode2" class="btn2" type="text" />
											<img id="RegImgCode2" src="temp/CF_CheckCode.gif" border="0" /><a href="#" onclick="RefresCode('reg','RegImgCode');return false;">看不清？换一张！</a></td>
									</tr>
								--%>
                    </table>
                </div>    <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
                </form>

                <script type="text/javascript">
                	$("#hidLogoID").val("<%=LogoID %>");
BindProvince("province","city","hidProvince","hidCity",true,false);
DropSetByText("txtOccuPation", <%= "\""+OccuPation+"\""%>);
<!--  
    //document.getElementById('pwd').focus();
    
    function onFormSubmit(f){
        
        
        //登录密码----------
        var password = document.getElementById('txtPassword');
        if(!alertNull(password,'请输入旧密码！')){
            return false;
        }
        
        
        //1.-------------------
        var pwd = document.getElementById('pwd');
        var pwd2 = document.getElementById('pwd2');
        if(pwd.value.trim().length>0){
            //valid regx-----------------
            if(!/^[0-9a-zA-Z]{6,20}$/.test(pwd.value.trim())){
                alert('密码由6-20个英文字母或数字组成，请重新输入！');
                pwd.focus();
                return false;
            }
            
            if(pwd.value.trim()!=pwd2.value.trim()){
                alert('两次输入密码不一致，请重新输入。');
                pwd2.focus();
                return false;
            }
        }
        
        
        //2.-------------------
        var nickname = document.getElementById('nickname');
        //valid is null--------------
        if(nickname.value.trim().length==0){
            alert("请输入昵称！");
            nickname.focus();
            return false;
        }
        else{
            //valid regx----------------- /^[_A-Za-z0-9\u4e00-\u9fa5]{2,20}$/.test(txt.value)
            if(nickname.value.trim().length<2 || nickname.value.trim().length>12){
                alert('昵称由字母、数字、特殊符号组成，长度为2-12位！');
                nickname.focus();
                return false;
            }
            
            //valid is exsits------------
            var urlData = '/Public/XmlHttpUser.aspx?type=upnickexist&nickname='+escape(nickname.value.trim());
            //alert(urlData);
            var strReturn = AjaxCall(urlData);
            //alert(strReturn);
            if(strReturn=="1"){
                alert('对不起，该昵称已经存在。');
                nickname.focus();
                return false;
            }
        }
        
        //3.---------------------
        var email = document.getElementById('email');
        if(email.value.trim().length>0){
            if(!/^[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}$/.test(email.value.trim())){
                alert('请按正确格式填写电子邮箱。');
                email.focus();
                return false;
            }
        }
        
        //验证QQ号格式;
        var qqnum=document.getElementById('qqnum');
        regqq=/^[0-9]{4,12}$/
        if(qqnum.value.trim().length>0)
        {
			if(!regqq.test(qqnum.value))
			{
				alert("QQ只能为4-12位的数字");
				qqnum.focus();
				return false;
			}
        }
        
        //
        var mobile = document.getElementById('mobile');
        if(mobile.value.trim().length>0){
            if(!/^(\(\d{3,4}\)|\d{3,4}-|\d{3})\d{7,8}$/.test(mobile.value.trim())){
                alert('电话号码格式不正确！区号以()或-隔开。');
                mobile.focus();
                return false;
            }
        }
        
        return true;
    }
 //-->
                </script>

            </div>
        </div>
    </div>
    <div class="clear">
    </div>
   <!--right End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
