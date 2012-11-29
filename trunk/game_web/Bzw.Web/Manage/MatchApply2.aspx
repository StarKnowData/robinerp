<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_MatchApply2" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="/style/css.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
   <script type="text/javascript" src="/Public/Js/AviodHotKey.js"></script> 
     <script type="text/javascript" src="/Public/Js/jquery.js"></script> 
     <script src="/Public/Js/public.js"></script>
      <meta  http-equiv="Pragma" content="no-cache" />
        <meta http-equiv="Cache-Control" content="no-cache" />
        <meta http-equiv="Expires" content="0" />
</head>
<body>
    <form id="form1" runat="server">
     <asp:Panel ID="panShow" runat="server"> 
               <asp:HiddenField  ID="hids" runat="server" /> <asp:HiddenField ID="hide" runat="server" /><asp:HiddenField ID="hidIsApply"  runat="server"/> <asp:HiddenField ID="hiduid" runat="server"   />
    <div class="Ma-Box">
        
        <div class="Ma-Time">
            <div class="timeImg" id="timer">  
                <table width="100%" height="100%" border="0" cellpadding="0" cellspacing="0">
                    <tr>
                        <td width="33%">
                            &nbsp;
                        </td>
                        <td width="12%" align="center">
                         <span id="hh"></span>
                        </td>
                        <td width="10%">
                            &nbsp;
                        </td>
                        <td width="14%" align="center">
                            <span id="mm"></span>
                        </td>
                        <td width="9%">
                            &nbsp;
                        </td>
                        <td width="12%" align="center">
                             <span id="ss"></span>
                        </td>
                        <td width="10%">
                            &nbsp;
                        </td>
                    </tr>
                </table>
                <div class="csButton">
                   	<input type="button" name="imageField2" class="but_01" value=" "  
						runat="server" id="imageField2"   />
                    <input type="button" name="btnExit" class="but_02" value=" "  
						id="btnExit" runat="server"     />
                    <!-- <a href="#"><img src="images/tsButton.jpg" /></a> -->
                </div>
            </div>
        </div>
        <div class="Ma-Intr">
            <ul>
                <li><span><strong>人数限制：</strong><%=LimitPeople%>人</span> <span><strong>比赛费用：</strong><%=NeedMoney%> <%=UiCommon.StringConfig.MoneyName %>（扣银行费用）</span></li>
                <li><span><strong>比赛时间：</strong><%=MatchDate%></span> <span><strong>报名条件：</strong><%=NeedMoney%> <%=UiCommon.StringConfig.MoneyName %></span>
                </li>
                <li><span><strong>配桌方式：</strong>比赛开始后系统将为您自动分配位置</span> <asp:Label ID="lblMsg" runat="server" CssClass="msg"></asp:Label></li>
               
            </ul>
        </div>
        <div class="ma-Content">
         <%=MatchContent %> 
        </div>
    </div>
    </asp:Panel>
    </form>
    <script type="text/javascript" language="javascript">
        $(document).ready(function() {

            $("#imageField2").click(match);
            $("#btnExit").click(exit);
        });
        var timeID;
        var date = "<%=JsServerTime %>";
        var date2 = "<%=JsStartTime %>";
        var dates = date.split(",");
        var dates2 = date2.split(",");
        var st = new Date(dates[0], dates[1], dates[2], dates[3], dates[4], dates[5]); //服务器当前时间
        var et = new Date(dates2[0], dates2[1], dates2[2], dates2[3], dates2[4], dates2[5]); ; //比赛开始时间

        var timer = document.getElementById("timer");
        var now = new Date();

        var diff = -480 - now.getTimezoneOffset();
        var leave_2 = (et.getTime() - st.getTime()) + diff * 60000;

        var maxtime = Math.floor(leave_2 / (1000));

        function CountDown() {
            if (maxtime > 0) {


                var hour_2 = Math.floor(maxtime / (3600));
                var minute_2 = Math.floor(maxtime / (60)) - (hour_2 * 60);

                var second_2 = Math.floor(maxtime) - (hour_2 * 60 * 60) - (minute_2 * 60);

                document.getElementById("hh").innerHTML = hour_2;
                document.getElementById("mm").innerHTML = minute_2;
                document.getElementById("ss").innerHTML = second_2;
                --maxtime;
            }
            else if (maxtime == 0) {

                location.href = "bzw://contest/begin?isapply=" + document.getElementById("hidIsApply").value;
            }
            else {

                window.clearInterval(timeID);
                //  location.href = "bzw://contest/begin?isapply=" + document.getElementById("hidIsApply").value;
            }
        }
        timeID = window.setInterval("CountDown()", 1000);
        function match() {
            var urlData = '/Public/XmlHttpUser.aspx?type=matchapply&id=' + document.getElementById("hide").value + '&token2=' + GetRequest("token", "") + '&uid=' + document.getElementById("hiduid").value;

            var strReturn = AjaxCall(urlData);
            if (strReturn == "报名成功！") {
                document.getElementById("imageField2").style.display = "none";
                document.getElementById("btnExit").style.display = "inline";
                document.getElementById("lblMsg").innerText = strReturn;
                document.getElementById("hidIsApply").value = "1";
            }
            else {
                document.getElementById("lblMsg").innerText = strReturn;
            }


        }
        function exit() {
            var urlData = '/Public/XmlHttpUser.aspx?type=matchexit&id=' + document.getElementById("hide").value + "&hidTime=" + document.getElementById("hids").value + '&token2=' + decodeURIComponent(GetRequest("token", "")) + '&uid=' + document.getElementById("hiduid").value; ;

            var strReturn = AjaxCall(urlData);
            if (strReturn == "退赛成功！") {
                document.getElementById("imageField2").style.display = "inline";
                document.getElementById("btnExit").style.display = "none";
                document.getElementById("hidIsApply").value = "0";
            }
            document.getElementById("lblMsg").innerText = strReturn;
        }
    </script>
</body>
</html>
