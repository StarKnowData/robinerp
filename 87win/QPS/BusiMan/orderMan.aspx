<%@ Page Title="" Language="C#" MasterPageFile="~/BusiMan/EnterMaster.Master" AutoEventWireup="true" CodeBehind="orderMan.aspx.cs" Inherits="QPS.Web.BusiMan.orderMan" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

        <div class="grright">
              <div class="grtitlea">
                    <span>订单管理</span>
             </div>
              <div class="grbox">
                    <asp:GridView ID="gdvOrder" runat="server" CellPadding="4" 
                       ForeColor="#333333" GridLines="None"  Width="100%"
                               DataKeyNames="订单编号" onrowcommand="gdvOrder_RowCommand" 
                        onrowdeleting="gdvOrder_RowDeleting" onrowupdating="gdvOrder_RowUpdating" 
                        onrowediting="gdvOrder_RowEditing" 
                        >
                       <RowStyle BackColor="#EFF3FB" />  　 　
                       <Columns>
                       <asp:TemplateField HeaderText="删除" ShowHeader="False" >
                   <ItemTemplate>
                   　<asp:LinkButton ID="BtnDelete" runat="server" CausesValidation="False" CommandName="Delete"
Text="删除" ForeColor="Black" OnClientClick="return confirm('确认要删除此行信息吗？')"></asp:LinkButton>
                   </ItemTemplate></asp:TemplateField>
                    <asp:ButtonField  CommandName="Update"  HeaderText="修改" Text="修改"  />
                                                <asp:TemplateField HeaderText="是否有效">
                                    <ItemTemplate>
                            <asp:LinkButton ID="lbtValidate" runat="server" CommandName="IsValidate" CommandArgument='<%# Eval("订单编号") +"|"+ Eval("是否有效") %>'><%# GetExamine(Convert.ToInt32(Eval("是否有效")))%></asp:LinkButton>    
                                    </ItemTemplate>
                                </asp:TemplateField> 
                   
                       </Columns>
                        <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                        <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                        <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                        <HeaderStyle BackColor="#FE6A6A" Font-Bold="True" ForeColor="White" />
                        <EditRowStyle BackColor="#2461BF" />
                        <AlternatingRowStyle BackColor="White" />
    </asp:GridView></div> </div>
</asp:Content>
