<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Lottery" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

    <script type="text/javascript" src="/Public/Js/marquee.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="8" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    抽奖</h3>
                <p class="dqwz">
                    当前位置：首页 > 抽奖</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <div id="Account">
                        <div class="rank_manu" id="record">
                            <a id="g1" href="/Manage/MyLoterryJP.aspx">我的奖品</a>&nbsp;&nbsp; |&nbsp;&nbsp;<a id="g2"
                                href="/Manage/LotteryLog.aspx">中奖名单</a>&nbsp;&nbsp;</div>
                        <div id="zj_c" style="width: 700px; height: 100px; border: 1px solid #d1d1d1; margin-top: 10px;
                            overflow: hidden;">
                            <%=ZJContent %></div>
                        <div style="width: 700px; margin-top: 10px;">
                            <h4>
                                说明：金所需<%=ConfigurationManager.AppSettings["moneyName"].ToString()%><%=gMoney %>&nbsp;&nbsp;
                                银所需<%=ConfigurationManager.AppSettings["moneyName"].ToString()%><%=sMoney %>
                                &nbsp;&nbsp; 玉所需<%=ConfigurationManager.AppSettings["moneyName"].ToString()%><%=jMoney %>
                                &nbsp;&nbsp;</h4>
                            <p>
                            </p>
                            <iframe src="/Upload/ZhuanPanMain.html" width="700px" height="600px" frameborder="0">
                            </iframe>
                        </div>
                        
                    </div>
                  
                </div>
            </div><p><img src="/Images/cont_img01.jpg" alt="" /></p>
            <div class="clear">
            </div>
        </div>
        <!--right End-->
    </div>
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />

    <script type="text/javascript">
        try {
            var marquee1 = new Marquee("zj_c");
            marquee1.Direction = "top";
            marquee1.Step = 2;
            marquee1.Width = 700;
            marquee1.Height = 100;
            marquee1.Timer = 100; //值小越快，值大越慢
            marquee1.DelayTime = 0;
            marquee1.WaitTime = 0;
            marquee1.ScrollStep = 1;
            marquee1.Start();
        } catch (e) { }
    

   
		
		
    </script>

</body>
</html>
