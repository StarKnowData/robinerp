<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DingDan.aspx.cs" Inherits="QPS.Web.Manage.AdminControl.DingDan" %>
<%--订单--%>
<!DOCTYPE Orderform as ohtml PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<%@ Register assembly="SdCms.Controls" namespace="SdCms.Controls" tagprefix="cc1" %>

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>订单管理</title>
    <style type="text/css">
        .style1
        {
            width: 118px;
        }
        .style2
        {
            width: 64px;
        }
        .style3
        {
            width: 64px;
            height: 13px;
        }
        .style4
        {
            width: 118px;
            height: 13px;
        }
        .style5
        {
            width: 59px;
            height: 13px;
        }
        .style6
        {
            height: 13px;
        }
        .style7
        {
            width: 59px;
        }
        .style8
        {
            width: 169px;
        }
        .style9
        {
            height: 13px;
            width: 169px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align:center;">
    <table width=90%>
        <tr >
            <td style="text-align:left; color:Red;">
                根据订单编号或者用户名查询：
            </td>
            <td style="text-align:left; color:Red;">
                根据棋牌室名或者手机号查询：
            </td>
        </tr>
    </table>
	<table width=50% border=0 cellpadding="3">
    <table width=90% border=0 cellpadding="3">
	    <tr>
	        <td align=left class="style2">订单编号</td>
	        <td align=left class="style1">
                <asp:TextBox ID="txtId" runat="server"></asp:TextBox>
	        </td>
	        <td align=left class="style7">&nbsp;</td>
	        <td align=left >
                棋牌室名</td>
	        <td align=left>
                <asp:TextBox ID="TextRname" runat="server"></asp:TextBox>
            </td>
            <td align=left>
                <asp:Button ID="Button2" runat="server" Text="新增" OnClick="Button2_Click" Visible="false" /></td>
	    </tr>
  
	    <tr>
	        <td align=left class="style3">用户名</td>
	        <td align=left class="style4">
	            <asp:TextBox ID=txtName runat=server ></asp:TextBox>
	        </td>
	        <%--<td align=left style="width: 90px">状&nbsp;&nbsp;&nbsp; 态</td>--%>
	  
	        <td align=left>
                <asp:Button ID="Button1" runat="server" Text="查询" OnClick="Button1_Click" 
                    Height="26px" />
	        </td>
	        <td align=left>手机号</td>
	        <td align=left class="style5">
                <%--<asp:TextBox ID="TextType" runat="server"></asp:TextBox>--%>
	                <asp:TextBox ID="Txtphone" runat="server"></asp:TextBox>
            
	                </td>
	        <td align=left>       
	                <asp:Button ID="Button3" runat="server" Text="查询" onclick="Button3_Click" />
            </td>
            <td class="style6">
            
	                &nbsp;</td>
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
							
							<asp:TemplateColumn HeaderText="订单号">
									<ItemTemplate>
									<asp:Label id="lblTestItems" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.Id") %>' ></asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
										
					<asp:TemplateColumn HeaderText="起始时间" >
						<ItemTemplate>
						<asp:Label id="lblId" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.StartTime") %>' ></asp:Label>
						</ItemTemplate>
                             <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
				    </asp:TemplateColumn>
								
				    <asp:TemplateColumn HeaderText="结束时间">
						<ItemTemplate>
						<asp:Label id="lblPhone" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.endTime") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
					
					<asp:TemplateColumn HeaderText="用户名">
						<ItemTemplate>
                            <asp:Label id="lblUserIDItem" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.Id") %>' Visible="False"></asp:Label>
							<asp:Label id="lblUserNameItem" runat="server" Text='<%# GetName(DataBinder.Eval(Container, "DataItem.username").ToString()) %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
					
					<asp:TemplateColumn HeaderText="手机号">
			        <ItemTemplate>
			        <asp:Label id="lblUserphone" runat="server" Text='<%# GetName(DataBinder.Eval(Container, "DataItem.PhoneNum").ToString()) %>' ></asp:Label>
				    </ItemTemplate>	
					</asp:TemplateColumn>
					
					
					
					<asp:TemplateColumn HeaderText="棋牌室名">
						<ItemTemplate>
							<asp:Label id="lblRoomItems" runat="server" Text='<%# GetName(DataBinder.Eval(Container, "DataItem.Name").ToString()) %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
					
					
					<asp:TemplateColumn HeaderText="状态" >
						<ItemTemplate>
                            <asp:Label ID="labRoomType" runat="server" Text='<%# Eval("RoomType") %>' Visible="false"></asp:Label>
                            <asp:LinkButton ID="libStartBtn" runat="server" CommandName="changStart" CommandArgument='<%# Eval("Id") +"|"+ Eval("RoomType") %>'><%# GetStart(Convert.ToInt32(Eval("RoomType")))%></asp:LinkButton>
						</ItemTemplate>
					</asp:TemplateColumn>
					
								
                                <asp:TemplateColumn HeaderText="修改" Visible="false">
                                    <ItemTemplate>
                                          <asp:LinkButton ID="lbtnDetail" runat="server" CommandName="LinkTo" >修改</asp:LinkButton>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
                                <asp:TemplateColumn HeaderText="删除">
                
                
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete" CommandArgument='<%# Eval("ID") %>' OnClientClick="javascript:return confirm('确认删除?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
							
                                <asp:TemplateColumn HeaderText="是否通过审核">
                                    <ItemTemplate>
                            <asp:LinkButton ID="libIsDelete" runat="server" CommandName="DeleteIs" CommandArgument='<%# Eval("id") +"|"+ Eval("IsDelete ") %>'><%# GetChecked(Convert.ToInt32(Eval("IsDelete ")))%></asp:LinkButton>    
                                    </ItemTemplate>
                                </asp:TemplateColumn>
							
							
							</Columns>
							<PagerStyle  Visible="False"></PagerStyle>
						</asp:datagrid>
                   
            </td>
	    </tr>
	     <tr><td width="100%" colspan="5"> 
             <cc1:pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" OnCommand="pager_Command" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" />
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
