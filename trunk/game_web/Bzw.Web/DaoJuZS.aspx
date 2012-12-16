<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DaoJuZS" %>

<%@ OutputCache Duration="60" VaryByParam="id" %>
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
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
     
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    游戏商城</h3>
                <p class="dqwz">
                    当前位置：首页 > 游戏商城</p>
            </div>
            <div id="sub_nr">
                <div id="props">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02">
                        <tr>
                            <td width="42%" align="right" valign="middle">
                                <img src="/Image/DaoJu/<%=PropID %>.gif" width="136" height="82" />
                            </td>
                            <td width="58%" class="prize_info">
                                <strong>道具名称：<%=PropName %></strong><br /> 道具介绍：<span class="textgray"><%=PropDesc %></span>
                            </td>
                        </tr>
                    </table>
                   
                    <div class="cz" style=" padding-top:15px;">
                
                        <form id="frmzs" action="" method="get" class="democss" onsubmit="return OnFormSubmit(this)">
                        <table width="100%" border="0" cellspacing="0" cellpadding="0">
                            <tr>
                                <th width="34%" height="30" align="right">
                                    赠送游戏账号：
                                </th>
                                <td width="66%">
                                    <input name="txtUserName" type="text" id="txtUserName" maxlength="20" class="fr_input" />
                                </td>
                            </tr>
                            <tr>
                                <th height="30" align="right">
                                    确认游戏账号：
                                </th>
                                <td>
                                    <input name="txtUserName2" type="text" id="txtUserName2" maxlength="20" class="fr_input" />
                                </td>
                            </tr>
                            <tr>
                                <th height="30" align="right">
                                    赠送数量：
                                </th>
                                <td>
                                    <input name="txtCount" type="text" id="txtCount" value="1" maxlength="3" size="5"
                                        class="fr_input" />
                                </td>
                            </tr>
                            <tr>
                                <td height="38" scope="row">
                                </td>
                                <td>
                                    <input type="submit" name="button5" id="button5" value="确认赠送" class="but_011" />
                                </td>
                            </tr>
                        </table>
                        </form>
                    </div>
                    <div class="clear">
                    </div>
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
            
        </div></div>
        <!--right End-->
        <!--footer-->
        <WebFooter:Control ID="webFooterone" runat="server" />
</body>

<script type="text/javascript">
    <!--
    function OnFormSubmit(f) {
        var djid = '<%=PropID %>';
        var djname = '<%=PropName %>';
        var msgfix = '赠送道具：' + djname + "\n\n";
        //--------
        var username = document.getElementById('txtUserName');
        var username2 = document.getElementById('txtUserName2');
        if (!alertNull(username, msgfix + '请输入赠送用户名！')) {
            username.focus();
            return false;
        }
        //----------
        if (username.value.toLowerCase().trim() != username2.value.toLowerCase().trim()) {
            alert(msgfix + '两次输入的赠送用户名不一致！');
            username2.focus();
            return false;
        }

        //--------
        var txt = document.getElementById('txtCount');
        if (!alertNull(txt, msgfix + '赠送数量不能为空！')) {
            txt.focus();
            return false;
        }
        else if (!/^([0-9])[0-9]*(\.\w*)?$/.test(txt.value.trim())) {
            alert(msgfix + '赠送数量必须是数字，并且大于零！');
            txt.focus();
            return false;
        } else if (parseInt(txt.value.trim()) == 0) {
            alert(msgfix + '赠送数量必须是数字，并且大于零！');
            txt.focus();
            return false;
        }


        //1.判断用户是否登录了，否就提示登录  //2.判断输入的用户名是不是存在，是不是自己(不允许是自己)  //3.判断自己的道具库里是否有这个道具，数量是否足够  //4.确认赠送
        var urlData = '/Public/XmlHttpUser.aspx?type=islogin';
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        if (strReturn == "0") {
            alert(msgfix + '对不起，请您登录后再赠送。');
            return false;
        }

        //--------
        if (!confirm(msgfix + '确认赠送该道具给[' + username.value + ']吗？')) {
            return false;
        }

        //2.根据数量乘于价格的结果，判断用户是否有足够的金币（银行或钱包）buydaoju
        urlData = '/Public/XmlHttpUser.aspx?type=zsdaoju&id=' + djid;
        urlData += '&targetname=' + escape(username.value.trim());
        urlData += '&count=' + txt.value.trim();
        //alert(urlData);
        strReturn = AjaxCall(urlData);
        //alert(strReturn);
        if (strReturn == "myself") {
            alert(msgfix + '抱歉，您不能把道具赠送给自己。');
        }
        else if (strReturn == "nouser") {
            alert(msgfix + '抱歉，被赠送用户不存在！');
        }
        else if (strReturn == "nodaoju") {
            alert(msgfix + '抱歉，您的道具库里没有这个道具或数量不够！');
        }
        else if (strReturn == "zsdjcg") {
            alert(msgfix + '道具赠送成功,您可以告诉您的好朋友[' + username.value + ']使用这个道具了！');
            username.value = '';
            username2.value = '';
            txt.value = 1;
        } else {
            alert(msgfix + '抱歉，道具赠送失败，可能是服务器繁忙，请稍候再试！');
        }

        return false;
    }
    //-->
</script>

</html>
