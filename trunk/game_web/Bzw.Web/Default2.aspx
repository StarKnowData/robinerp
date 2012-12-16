<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Default2" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebService.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<%@ Register TagName="WebLeft" TagPrefix="BZW" Src="~/Public/WebLeft.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
   <title> 
	</title>
	 
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/FlashPlayer.js"></script>
    <script type="text/javascript" src="/Public/Js/marquee.js"></script>
    <script type="text/javascript" src="/Public/Js/topbtn.js"></script>
    <script type="text/javascript" src="/Public/Js/submu.js"></script>
     <script type="text/javascript" src="/Public/Js/index.js"></script>
    <script type="text/jscript">
        $(document).ready(
		function() {

		    if ($("#photolist > ul > li").length > 3) {
		        var dl = document.getElementById('photolist');
		        var dt = dl.getElementsByTagName('li')[$("#photolist > ul > li").length - 3];

		        var speed = 50;
		      
		        var rolling = function() {

		            if (dl.scrollLeft == dt.offsetLeft) {

		                dl.scrollLeft = 0;
		            }
		            else {

		                dl.scrollLeft++;
		            }
		        }
		        var timer = setInterval(rolling, speed)//设置定时器  
		        dl.onmouseover = function() { clearInterval(timer) } //鼠标移到marquee上时，清除定时器，停止滚动  
		        dl.onmouseout = function() { timer = setInterval(rolling, speed) } //鼠标移开时重设定时器
		    }

		    $.get('/upload/xml/GameAd.xml', function(d) {
		        $(d).find('item').each(function() {
		            var $item = $(this);
		            var id = $item.attr("id");
		            var content = $item.find("Content").text();
		            if (id == 5)
		                $("#ad5").html(content);
		            //    MM_preloadImages();
		        });
		    });
		}
	);
    </script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTop" runat="server" pageType="1" />
        <!-- left start -->
        <div id="left">
            <BZW:WebShortCutKey ID="webCutKey" runat="server" />
            <BZW:WebLeft ID="webLeft" runat="server"></BZW:WebLeft>
        </div>
        <!-- left end -->
        <!-- content start -->
        <div id="content">
            <div id="cont">
                <div style="width:733px; height:177px;">
                <%=GetFlashJS(733, 177, 5)%></div>
                <div id="cont_nr">
                    <div id="xw">
                        <p class="index_tit01">
                            <img src="/Images/cont_btn01on.jpg" alt="" onmouseover="ChangeNewType(1)" id="news1"
                                style="cursor: hand" /><img src="/Images/cont_btn02off.jpg" alt="" onmouseover="ChangeNewType(2)"
                                    id="news2" style="cursor: hand" /><span style=" position:absolute; left:413px; top:3px;"><a href="/NewsList.aspx">更多+</a>&nbsp;&nbsp;&nbsp;&nbsp;</span>   </p>
                   
                        <ul id="news1l" style="display: block;">
                            <asp:Repeater ID="rptNews" runat="server">
                                <ItemTemplate>
                                    <li><span 
                                            class="fr" ><%#Eval("Issue_Time","{0:yyyy-MM-dd}")%></span><span   ><a href='/News2.aspx?id=<%#Eval("News_ID") %>' title='<%#Eval("Title") %>'
                                        style='color: <%#Eval("TitleColor").ToString() == "black" ? "#555454" : Eval("TitleColor")%>;'>
                                        <%#Utility.Common.CutStringUnicode( Eval("Title").ToString(),40,"...") %></a></span></li>
                                </ItemTemplate>
                            </asp:Repeater>
                        </ul>
                        <ul id="news2l" style="display: none;">
                            <asp:Repeater ID="rptQuesNews" runat="server">
                                <ItemTemplate>
                                    <li><span
                                            class="fr"><%#Eval("Issue_Time","{0:yyyy-MM-dd}")%></span><span ><a href='/News2.aspx?id=<%#Eval("News_ID") %>' title='<%#Eval("Title") %>'
                                        style='color: <%#Eval("TitleColor").ToString() == "black" ? "#555454" : Eval("TitleColor")%>;;'>
                                        <%#Utility.Common.CutStringUnicode( Eval("Title").ToString(),40,"...") %></a></span></li>
                                </ItemTemplate>
                            </asp:Repeater>
                        </ul>
                        <p>
                            <img src="/Images/cont_tbl_img01.jpg" alt="" /></p>
                    </div>
                    <div id="phb">
                        <p class="index_tit01">
                            <img src="/Images/cont_tit01.jpg" alt="" /><span style=" position:absolute; left:413px; top:3px;"><a href="/ContestRank.aspx">更多+</a>&nbsp;&nbsp;&nbsp;&nbsp;</span></p>
                        <div>
                            <ul>
                                <asp:Repeater ID="rptGameRank" runat="server">
                                    <ItemTemplate>
                                       
                                        <li class='<%=(rankid==4)?"bg03":"bg02" %>' id="gr<%=rankid %>" <%=(rankid==4)?"style='width:89px'":"" %> onmouseover="ChangeMatch(<%=rankid %>)" ><span style="cursor: hand"><%#Utility.Common.CutStringUnicode( Eval("Name").ToString(),12,"") %></span></li>

                                        <% rankid = rankid + 1;%>
                                    </ItemTemplate>
                                </asp:Repeater>
                               <%rankid = 0; %>
                                
                            </ul>
                        </div>
                        <div id="bs">
                            <table width="441" summary="" border="0" id="gl0l"  style="display:none;">
                                <caption>
                                </caption>
                                <colgroup>
                                    <col width="26%" />
                                    <col width="21%" />
                                    <col width="26%" />
                                    <col width="26%" />
                                </colgroup>
                                <thead>
                                    <tr>
                                        <th scope="col">
                                            名次
                                        </th>
                                        <th scope="col">
                                            昵称
                                        </th>
                                        <th scope="col">
                                            局数
                                        </th>
                                        <th scope="col">
                                            比赛积分
                                        </th>
                                    </tr>
                                </thead>
                                <tbody >
                                <%rankid = 0; %>
                                <asp:Repeater ID="rptMatchRank1" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                            NO.<%=rankid=rankid+1 %>
                                        </td>
                                        <td class="font01">
                                            <%#Eval("NickName")%>
                                        </td>
                                        <td>
                                            <%#Eval("ContestCount")%>
                                        </td>
                                        <td>
                                            <%#Eval( "Score" ) %> 
                                        </td>
                                    </tr>
                                </ItemTemplate>
                                </asp:Repeater>
                                  
                                </tbody>
                            </table>
                            <table width="441" summary="" border="0" id="gl1l" style="display:none;">
                                <caption>
                                </caption>
                                <colgroup>
                                    <col width="26%" />
                                    <col width="21%" />
                                    <col width="26%" />
                                    <col width="26%" />
                                </colgroup>
                                <thead>
                                    <tr>
                                        <th scope="col">
                                            名次
                                        </th>
                                        <th scope="col">
                                            昵称
                                        </th>
                                        <th scope="col">
                                            局数
                                        </th>
                                        <th scope="col">
                                            比赛积分
                                        </th>
                                    </tr>
                                </thead>
                                <tbody >
                                 <%rankid = 0; %>
                                      <asp:Repeater ID="rptMatchRank2" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                            NO.<%=rankid=rankid+1 %>
                                        </td>
                                        <td class="font01">
                                            <%#Eval("NickName")%>
                                        </td>
                                        <td>
                                            <%#Eval("ContestCount")%>
                                        </td>
                                        <td>
                                            <%#Eval( "Score" ) %> 
                                        </td>
                                    </tr>
                                </ItemTemplate>
                                </asp:Repeater>
                                </tbody>
                            </table>
                            <table width="441" summary="" border="0" id="gl2l" style="display:none">
                                <caption>
                                </caption>
                                <colgroup>
                                    <col width="26%" />
                                    <col width="21%" />
                                    <col width="26%" />
                                    <col width="26%" />
                                </colgroup>
                                <thead>
                                    <tr>
                                        <th scope="col">
                                            名次
                                        </th>
                                        <th scope="col">
                                            昵称
                                        </th>
                                        <th scope="col">
                                            局数
                                        </th>
                                        <th scope="col">
                                            比赛积分
                                        </th>
                                    </tr>
                                </thead>
                                <tbody > <%rankid = 0; %>
                                               <asp:Repeater ID="rptMatchRank3" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                        
                                            NO.<%=rankid=rankid+1 %>
                                        </td>
                                        <td class="font01">
                                            <%#Eval("NickName")%>
                                        </td>
                                        <td>
                                            <%#Eval("ContestCount")%>
                                        </td>
                                        <td>
                                            <%#Eval( "Score" ) %> 
                                        </td>
                                    </tr>
                                </ItemTemplate>
                                </asp:Repeater>
                                </tbody>
                            </table>
                            <table width="441" summary="" border="0" id="gl3l" style="display:none">
                                <caption>
                                </caption>
                                <colgroup>
                                    <col width="26%" />
                                    <col width="21%" />
                                    <col width="26%" />
                                    <col width="26%" />
                                </colgroup>
                                <thead>
                                    <tr>
                                        <th scope="col">
                                            名次
                                        </th>
                                        <th scope="col">
                                            昵称
                                        </th>
                                        <th scope="col">
                                            局数
                                        </th>
                                        <th scope="col">
                                            比赛积分
                                        </th>
                                    </tr>
                                </thead>
                                <tbody > <%rankid = 0; %>
                                       <asp:Repeater ID="rptMatchRank4" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                            NO.<%=rankid=rankid+1 %>
                                        </td>
                                        <td class="font01">
                                            <%#Eval("NickName")%>
                                        </td>
                                        <td>
                                            <%#Eval("ContestCount")%>
                                        </td>
                                        <td>
                                            <%#Eval( "Score" ) %> 
                                        </td>
                                    </tr>
                                </ItemTemplate>
                                </asp:Repeater>
                                </tbody>
                            </table>
                            <table width="441" summary="" border="0" id="gl4l"  >
                                <caption>
                                </caption>
                                <colgroup>
                                    <col width="26%" />
                                    <col width="21%" />
                                    <col width="26%" />
                                    <col width="26%" />
                                </colgroup>
                                <thead>
                                    <tr>
                                        <th scope="col">
                                            名次
                                        </th>
                                        <th scope="col">
                                            昵称
                                        </th>
                                        <th scope="col">
                                            局数
                                        </th>
                                        <th scope="col">
                                            比赛积分
                                        </th>
                                    </tr>
                                </thead>
                                <tbody > <%rankid = 0; %>
                                        <asp:Repeater ID="rptMatchRank5" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                            NO.<%=rankid=rankid+1 %>
                                        </td>
                                        <td class="font01">
                                            <%#Eval("NickName")%>
                                        </td>
                                        <td>
                                            <%#Eval("ContestCount")%>
                                        </td>
                                        <td>
                                            <%#Eval( "Score" ) %> 
                                        </td>
                                    </tr>
                                </ItemTemplate>
                                </asp:Repeater>
                                </tbody>
                            </table>
                        </div>
                        <p>
                            <img src="/Images/cont_tbl_img02.jpg" alt="" /></p>
                    </div>
                    <div id="hdxp" >
                        <h3 class="fl">
                            <img src="/Images/cont_tit02.jpg" alt="" /></h3>
                            <div id="photolist" style="width:397px; overflow:hidden; position:relative;  ">
                        <ul  style=" width:600%;  ">
                            <asp:Repeater ID="rptPhotoList" runat="server">
                                <ItemTemplate>
                                  <li><a href='/UserInfo/PhotoList.aspx?params=<%# Eval( "ColumnID" ) %>' title='<%# Eval( "NickName" ).ToString()%>'>
                                        <img src='/Public/Thumbs.aspx?path=<%# Server.UrlEncode( Eval( "PicPath" ).ToString() ) %>'
                                            width="120px" height="86px" alt="" /></a></li>
                                </ItemTemplate>
                                
                            </asp:Repeater>
                             
                        </ul>
                        </div>
                    </div>
                </div>
                <div id="cont_r">
                    <div id="mrt">
                        <h3>
                            <img src="/Images/right_tit01.jpg" alt="" /></h3>
                        <div class="top_btn01">
                            <ul>
                                <li class="bg05" onmouseover="ChangeOrd(this)" id="sp1"><span style="cursor: hand">金币</span></li>
                                <li class="bg06" onmouseover="ChangeOrd(this)" id="sp2"><span style="cursor: hand">魅力</span></li>
                                <li class="bg06" onmouseover="ChangeOrd(this)" id="sp3"><span style="cursor: hand">
                                    <%=UiCommon.StringConfig.GoldName%></span></li>
                                <li class="bg08" onmouseover="ChangeOrd(this)" id="sp4" style="width: 57px;"><span
                                    style="cursor: hand">时间</span></li>
                            </ul>
                        </div>
                        <div class="mrt_list">
                           <%rankid = 0; %>
                            <ul id="sp1l">
                            
                                <asp:Repeater ID="rpCaifu" runat="server">
                                    <ItemTemplate>
                                        <li><span
                                                class="fr"><%#Eval( "SumMoney" )%></span><span>NO.<%=rankid=rankid+1 %></span><span class="l10"><img src="/Images/right_line01.jpg"
                                            alt="" /></span><span class="l10"><%# Utility.Common.CutStringUnicode( Eval("NickName").ToString(),26,"") %></span></li>
                                    </ItemTemplate>
                                </asp:Repeater>
                            </ul>
                            <%rankid = 0; %>
                            <ul id="sp2l" style="display: none">
                                <asp:Repeater ID="rpMeili" runat="server">
                                    <ItemTemplate>
                                        <li><span
                                                class="fr"><%#Eval("meili")%></span><span>NO.<%=rankid=rankid+1 %></span><span class="l10"><img src="/Images/right_line01.jpg"
                                            alt="" /></span><span class="l10"><%# Utility.Common.CutStringUnicode( Eval("NickName").ToString(),26,"") %></span></li>
                                    </ItemTemplate>
                                </asp:Repeater>
                            </ul>
                            <%rankid = 0; %>
                            <ul id="sp3l" style="display: none">
                                <asp:Repeater ID="rptLotteries" runat="server">
                                    <ItemTemplate>
                                        <li><span
                                                class="fr"><%#UiCommon.StringConfig.AddZeros(Eval("Lotteries"))%></span><span>NO.<%=rankid=rankid+1 %></span><span class="l10"><img src="/Images/right_line01.jpg"
                                            alt="" /></span><span class="l10"><%# Utility.Common.CutStringUnicode( Eval("NickName").ToString(),26,"") %></span></li>
                                    </ItemTemplate>
                                </asp:Repeater>
                            </ul>
                            <%rankid = 0; %>
                            <ul id="sp4l" style="display: none">
                                <asp:Repeater ID="rptGameTime" runat="server">
                                    <ItemTemplate>
                                        <li><span
                                                class="fr"><%#member.ConverTimeToDHMS2(Eval("PlayTimeCount").ToString())%></span><span>NO.<%=rankid=rankid+1 %></span><span class="l10"><img src="/Images/right_line01.jpg"
                                            alt="" /></span><span class="l10"><%# Utility.Common.CutStringUnicode( Eval("NickName").ToString(),26,"") %></span></li>
                                    </ItemTemplate>
                                </asp:Repeater>
                            </ul>
                        </div>
                        <p>
                            <img src="/Images/right_img01.jpg" alt="" /></p>
                    </div><div id="ad5" style=" height:148px;">
                    </div>
                    <p>
                        <a href="#">
                            <img src="/Images/right_baner02.jpg" alt="" /></a></p>
                </div>
            </div>
        </div>
    </div>
    <WebFooter:Control ID="webfooter1" runat="server" />
</body>



</html>
