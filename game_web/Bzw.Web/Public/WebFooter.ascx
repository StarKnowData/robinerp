<%@ Control Language="C#" ClassName="WebFooter" %>
 <%@ Register TagName="Control" TagPrefix="WebQQ" Src="~/Public/WebQQ.ascx" %>
 
<div id="footer">
			<div id="dz">
				<p><img src="/Images/btm_line01.jpg" alt="" /></p>
				<p class="cb fl text02">
                               <span class="text03">禁止任何利用游戏进行赌博的行为，让我们共同净化游戏环境，一旦发现有违反用户协议的行为（包括赌博行为），我们将立刻封杀帐号！</span><br />
							   <span class="text03">版权所有 © <%= SiteConfig.GetParaValue("Copyright")%>  版权所有 </span><br />
							   <span class="text03">网站备案/许可证号 <%= SiteConfig.GetParaValue("SiteICP")%> </span>
				</p>
                <!-- 
                <h2><img src="/Images/btm_logo01.jpg" alt="" /></h2>
                -->
			</div>
</div>




<WebQQ:Control ID="WebQQ1" runat="server" />