<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Qps.aspx.cs" Inherits="QPS.Web.Manage.AdminControl.Qps" %>

<%@ Register Assembly="SdCms.Controls" Namespace="SdCms.Controls" TagPrefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%--棋牌室--%>
<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    </style>
    <style type="text/css">
        .style2
        {
            width: 374px;
        }
        .style3
        {
            width: 80px;
        }
        .style4
        {
            width: 127px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align:center;">
    
        <table width=90% border=0 cellpadding="3">
            <tr>
            <td style="text-align:left; color:Red;" class="style2">根据姓名和类型查询:
            </td>
        <td style="text-align:left; color:Red; background:"red">
        
            根据价格或着地域查询</td>
            <td>&nbsp;</td>
            <td></td>
            <td></td>
            </tr>   
    </table>
	<table width=90% border=0 cellpadding="3">
        <tr>
	        <td align=left class="style3">棋牌室名称</td>
	        <td align=left class="style4">
                <asp:TextBox ID="txtName" runat="server" Height="22px"></asp:TextBox>
	        </td>
	        <td align=left style="width: 90px">价&nbsp;&nbsp;&nbsp;&nbsp; 格</td>
	        <td style="width: 167px" align=left>
                <asp:TextBox ID="TextPrice" runat="server"></asp:TextBox>
	        </td>
	        <td align=left>
                <asp:Button ID="Button1" runat="server" Text="查询" OnClick="Button1_Click" />
                <asp:Button ID="Button2" runat="server" Text="新增" OnClick="Button2_Click" />&nbsp;
            </td>
	    </tr>
	    
	    <tr>
	        <td align=left class="style3">类&nbsp;&nbsp;&nbsp;&nbsp; 型</td>
	        <td align=left class="style4">
	            <asp:TextBox ID=txtType runat=server></asp:TextBox>
	        </td>
	        <td align=left style="width: 90px">地&nbsp;&nbsp;&nbsp;&nbsp; 域</td>
	        <td style="width: 167px" align=left>
	            <asp:TextBox ID=TextAre runat=server></asp:TextBox>
	        </td>
	        <td align=left>
                <asp:Button ID="Button3" runat="server" Text="查询" onclick="Button3_Click"  />
                &nbsp;
            </td>
	    </tr>
	    
	    
	    
	    <tr>
	        <td colspan=5 align=center>
	        <asp:datagrid id="dgExamProj" PageSize="20" GridLines="Horizontal" BackColor="White" BorderColor="Black"
							CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6" AutoGenerateColumns="False"
							AllowSorting="True" Font-Names="Verdana" AllowPaging="True" Runat="server" Width="100%" OnItemDataBound="dgExamProj_ItemDataBound" OnItemCommand="dgExamProj_ItemCommand">
							<SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080"/>
							<AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
							<ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></ItemStyle>							<HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></HeaderStyle>
							<Columns>
							
							<asp:TemplateColumn HeaderText="棋牌室名称">
									<ItemTemplate>
									<asp:Label id="lblPack" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.Id") %>' Visible="False"></asp:Label>
									<asp:Label id="lblName" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.Name") %>' ></asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
										
					<asp:TemplateColumn HeaderText="类型" >
						<ItemTemplate>
						<asp:Label id="lblRoomType" runat="server" Text='<%# GetType(DataBinder.Eval(Container, "DataItem.RoomType").ToString()) %>' ></asp:Label>
						</ItemTemplate>
                             <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
				    </asp:TemplateColumn>
								
				    <asp:TemplateColumn HeaderText="价格">
						<ItemTemplate>
						<asp:Label id="lblPrice" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.RoomPrice") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
					
					<asp:TemplateColumn HeaderText="地域">
						<ItemTemplate>
							<asp:Label id="lblAre" runat="server" 
                                Text='<%# DataBinder.Eval(Container, "DataItem.Are") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
					
					<asp:TemplateColumn HeaderText="详细地址">
						<ItemTemplate>
							<asp:Label id="lblAddress" runat="server" 
                                Text='<%# DataBinder.Eval(Container, "DataItem.Address") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
<%------------------------------------------------------%>
                                <asp:TemplateColumn HeaderText="是否推荐">
                                    <ItemTemplate>
                            <asp:LinkButton ID="libStartBtn" runat="server" CommandName="changStart" CommandArgument='<%# Eval("id") +"|"+ Eval("IfRecommend") %>'><%# GetStart(Convert.ToInt32(Eval("IfRecommend")))%></asp:LinkButton>    
                                    </ItemTemplate>
                                </asp:TemplateColumn>
                                
                                <asp:TemplateColumn HeaderText="是否通过审核">
                                    <ItemTemplate>
                            <asp:LinkButton ID="libExamine" runat="server" CommandName="Examine" CommandArgument='<%# Eval("id") +"|"+ Eval("IfExamine") %>'><%# GetExamine(Convert.ToInt32(Eval("IfExamine")))%></asp:LinkButton>    
                                    </ItemTemplate>
                                </asp:TemplateColumn>
                                
	
                                <asp:TemplateColumn HeaderText="修改">
                                    <ItemTemplate>
                                          <asp:LinkButton ID="lbtnDetail" runat="server" CommandName="LinkTo" CommandArgument='<%# DataBinder.Eval(Container, "DataItem.id") %>' >修改</asp:LinkButton>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"  Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"  Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
                                
                                <asp:TemplateColumn HeaderText="删除">
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete" CommandArgument='<%# Eval("ID") %>' OnClientClick="javascript:return confirm('确认删除?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
							
								
							</Columns>
							<PagerStyle  Visible="False"></PagerStyle>
						</asp:datagrid>
                   
             </td>
	    </tr>
	     <tr><td width="100%" colspan="5"> 
	         
             <cc1:Pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" 
                 oncommand="Pager1_Command1" />
                 
	         </td></tr>

   
	</table>
	
	</div>
    </form>
        <script language="javascript" type="text/javascript">
            function SeleAct(obj) {
                if (obj == "remove") {
                    document.getElementById("CategoryTitle").className = 'show';
                    document.getElementById("Button1").className = 'show';
                }
                else {
                    document.getElementById("CategoryTitle").className = 'hidden';
                    document.getElementById("Button1").className = 'hidden';
                }
            }
     </script>
</body>
</html>
