<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Service" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTop" runat="server" pageType="9" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webCutKey" runat="server" />
            <WebService:Control ID="webService" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    客服中心</h3>
                <p class="dqwz">
                    当前位置：首页 > 客服中心</p>
            </div><form id="Form1" runat="server" onsubmit="return onFormSubmit(this);">
            <div id="sub_nr">
                <div class="cz">
                    <p>
                        <img src="/Images/cont_tbl_img24.jpg" alt="" /></p>
                    <p>
                        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;严禁制用、转载、链接色情的，危害国家安全与社会安定的、危害民族或宗教团结等违法内容；一经发现将立即关闭；情节严<br />
                        重者直接移交相关部门处理。</p>
                        
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
                                        * 您的名字</label>
                                </th>
                                <td>
                                    <asp:TextBox ID="txtName" runat="server" MaxLength="15" CssClass="in"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id02">
                                        * 电子邮箱</label>
                                </th>
                                <td>
                                    <asp:TextBox ID="txtEmail" runat="server" MaxLength="25" CssClass="in"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        * 留言标题</label>
                                </th>
                                <td>
                                    <asp:TextBox ID="txtTitle" runat="server" MaxLength="25" CssClass="in"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id04">
                                        * 留言内容</label>
                                </th>
                                <td style="padding: 7px 0 7px 10px;">
                                    <asp:TextBox ID="txtContent" runat="server" CssClass="in" Height="94px" TextMode="MultiLine"
                                        Width="336px"/><br /><span class="text06">*（留言内容不能超过200位，一个汉字为2位。）</span>
                                </td>
                            </tr>
                            
                            <tr>
				                <th height="30" align="right" scope="row">
					                * 验证码：</th>
				                <td>
					                <asp:TextBox ID="VerifyCode" runat="server" MaxLength="4" CssClass="fr_input" Width="50"></asp:TextBox>
					                <img id="imgValidCode" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                                        alt="点击换一张图片" src="/Public/Getcode.aspx" style="vertical-align: top; cursor: pointer;
                                                        width: 50px; height: 16px" />
                                                        
                                    <span class="red">*</span></td>
			                </tr>
			                
                        </tbody>
                    </table>
                    <p class="cz_btn">
                        <input type="submit" name="imageField2" class="but_01" value=" " onserverclick="button5_ServerClick"    runat="server" id="imageField2" />&nbsp;&nbsp;&nbsp;&nbsp;
                        <input type="button" name="imageField3" class="but_02" value=" " onclick="ClearInfo()"  id="imageField3" />
                    </p>
                    <p>
                        <span id="spanMsg"></span>
                    </p>
                </div>
            </div></form>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--right End-->
    <!--footer-->
    <WebFooter:Control ID="webfooter1" runat="server" />

    <script type="text/javascript">
<!--
        function ClearInfo() {
            document.getElementById('txtName').value = '';
            document.getElementById('txtEmail').value = '';
            document.getElementById('txtTitle').value = '';
            document.getElementById('txtContent').value = '';
        }

        function onFormSubmit(f) {
            var txtName = document.getElementById('txtName');
            if (!alertNull(txtName, '请输入您的名字！')) {
                return false;
            }

            var txtEmail = document.getElementById('txtEmail');
            if (!alertNull(txtEmail, '请输入您的电子邮箱！')) {
                return false;
            } else if (!isEmail(txtEmail.value)) { //if(!/^[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}$/.test(txt.value)){
                alert('请输入正确格式的电子邮箱!');
                txtEmail.focus();
                return false;
            }

            var txtTitle = document.getElementById('txtTitle');
            if (!alertNull(txtTitle, '请输入留言的标题！')) {
                return false;
            }

            var txtContent = document.getElementById('txtContent');
            if (!alertNull(txtContent, '请输入留言的内容！')) {
                return false;
                
            }
            else {
                var strLen = 0;
                for (i = 0; i < txtContent.value.length; i++) {
                    if (txtContent.value.charCodeAt(i) > 255) {
                        strLen += 2; //是汉字则加2
                    }
                    else {
                        strLen++; //非汉字则加1
                    }
                }

                if (strLen > 200) {
                    alert('留言内容不能超过200位,您输入了' + strLen + '位！(一个汉字为2位)');
                    txtContent.focus();
                    return false;
                }
            }
                            var verify = document.getElementById('VerifyCode');
                                if (verify.value.length != 4 )
                                {
                                      alert('请输入四位验证码！');
										verify.focus();
										return false;
                                }

            return true;
        }
//-->
    </script>

    <script>
        var x = location.search;
        if (x != "") {
            if (x.replace("?", "").toLowerCase() == "success")
                document.getElementById("spanMsg").innerHTML = '<strong style="color:red;">提交成功！</strong>';
            else
                document.getElementById("spanMsg").innerHTML = '<strong style="color:red;">提交失败！</strong>';
        }
    </script>

</body>
</html>
