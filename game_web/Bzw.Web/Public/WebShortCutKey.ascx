<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="WebShortCutKey.ascx.cs" Inherits="Bzw.Web.Public.WebShortCutKey" %>
 

 		
			<p><a href="<%= smallUrl%>" title="游戏下载"><img src="/Images/left_btn01.jpg" alt="游戏下载" border="0" /></a></p>
			<p><a href="/Manage/Reg.aspx" title="用户注册"><img src="/Images/left_btn02.jpg" alt="用户注册"  border="0"/></a></p>
			<p><%if (!UiCommon.UserLoginInfo.IsLogin)
        { %><a href="/Manage/Login.aspx" title="个人中心"><%}
        else
        { %><a href="/Manage/Default.aspx" title="个人中心"><%} %><img src="/Images/left_btn03.jpg" alt="个人中心"  border="0"/></a></p>
			<p><a href="/Manage/Pay/Default.aspx" title="在线充值"><img src="/Images/left_btn04.jpg" alt="在线充值"  border="0"/></a></p>
			<p><a href="/Daoju.aspx" title="游戏商城"><img src="/Images/left_btn05.jpg" alt="游戏商城"  border="0"/></a></p>
			<p><a href="/ContestRank.aspx" title="比赛专区"><img src="/Images/left_btn06.jpg" alt="比赛专区"  border="0"/></a></p>
			<p><a href="#"><img src="/Images/left_btn07.jpg" alt=""  border="0"/></a></p>
			<p id="ad4" style="height:185px;"><a href="#"><img src="/Images/left_btn08.jpg" alt=""  border="0"/></a></p>
			
	 <script type="text/javascript">
    $(document).ready(function() {
        $.get('/upload/xml/GameAd.xml', function(d) {
            $(d).find('item').each(function() {
                var $item = $(this);
                var id = $item.attr("id");
                var content = $item.find("Content").text();
                if (id == 4)
                    $("#ad4").html(content);
                //    MM_preloadImages();
            });
        });
    });
</script>