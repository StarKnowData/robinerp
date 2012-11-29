<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="WebLeft.ascx.cs" Inherits="Bzw.Web.Public.WebLeft" %> 
        		 <div id="xszn">
				<h3><img src="/Images/left_tit01.jpg" alt="新手指南" /></h3>
				<ul>                    <asp:Repeater ID="rptNewUsers" runat="server">
                    <ItemTemplate>
                    <li ><a href='/News2.aspx?id=<%#Eval("News_ID") %>'><%#Utility.Common.CutStringUnicode( Eval("Title").ToString(),24,"...") %></a></li>
                    </ItemTemplate>
                    </asp:Repeater>
         		 
        		</ul>	</div>
        		 
        