<%@ Control Language="C#" ClassName="WebService" %>
 
<div class="righttop">
        	<ul>
        		<li class="zxzx">
                <a href="tencent://message/?uin=<%= SiteConfig.GetParaValue("CustomServiceQQ1")%>&Site=<%= SiteConfig.GetParaValue("Title")%>&Menu=yes" title="在线咨询">
                <img src="/images/Bn_phone.jpg" />
                 </a>
                </li>   
         		<li class="QQ"><img src="/images/qq.jpg" />
                	<h2><%= SiteConfig.GetParaValue("UserQQColony1")%></h2>
                	<h2><%= SiteConfig.GetParaValue("UserQQColony2")%></h2>
                	<h2><%= SiteConfig.GetParaValue("UserQQColony3")%></h2>
                </li> 
         		<li class="telephone"><img src="/images/phone.jpg" />
                	<h1><%= SiteConfig.GetParaValue("CustomServicePhone")%></h1>
                </li> 
        	</ul> 
        </div> 
 