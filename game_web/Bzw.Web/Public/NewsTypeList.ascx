<%@ Control Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Public.Public_NewsTypeList"%>
 

<div id="xwzx">
					<ul>
						 
						<asp:Repeater ID="rpNewType" runat="server">
				<ItemTemplate>
					<li><a href="<%# "/NewsList.aspx?tid=" + Eval( "Typeid" )%>" title="<%#Eval("TypeName") %>" class="link03">
						<%#Eval("TypeName")%>
					</a>
					</li>
				</ItemTemplate>
			</asp:Repeater>
					 
					</ul>
				</div>