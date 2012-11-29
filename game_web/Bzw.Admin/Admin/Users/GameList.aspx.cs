using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;
using System.Text;


public partial class Admin_Games_GameList : AdminBasePage
{
    public string usernames;
    public string seachids;
    
    public int listids = 0;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("09");
        txtBegin.Attributes.Add("onfocus", "WdatePicker({maxDate:'#F{$dp.$D(\'txtEnd\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'});");
        txtEnd.Attributes.Add("onfocus", "WdatePicker({minDate:'#F{$dp.$D(\'txtBegin\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'});");

        if (!IsPostBack)
        {
            BindGameNames();
            BindList();
        }
    }
    //游戏名称集合
    public void BindGameNames()
    {
        DataTable dt = new BLL.Game().ListTGameNameInfo(0);
        if (dt.Rows.Count > 0)
        {
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                ddlNameID.Items.Add(new ListItem(dt.Rows[i]["ComName"].ToString(), dt.Rows[i]["NameID"].ToString()));
            }
        }
        ddlNameID.Items.Insert(0, new ListItem("--请选择--", "-1"));

    }
    protected void BindList()
    {

        string userid = Utility.Common.GetStringOfUrl("userid");
        if (userid.Length > 0 && Utility.Common.IsNumber(userid))
        {
            string where = " and UserID=" + userid + " ";


            if (ddlNameID.SelectedValue != "-1")
            {
                where += " and GameNameID = " + ddlNameID.SelectedValue + " ";
            }

            if (!string.IsNullOrEmpty(txtBegin.Text))
            {
                where += " and EndTime >='" + txtBegin.Text.Trim() + " 00:00:00' ";// " 00:00:00' ";
            }
            if (!string.IsNullOrEmpty(txtEnd.Text))
            {
                where += " and EndTime <='" + txtEnd.Text.Trim() + " 23:59:59' ";// " 23:59:59' ";
            }

            //加上输赢金币不为0的约束 黄明森 2010-04-09
            where += " and ChangeMoney<>0";

            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
              .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
              .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
              .AddInputParameter("@Columns", DbType.String, "ID,RoomName,DeskIndex,GameTime,EndTime,Tax,UserID,ChangePoint,SrcMoney,ChangeMoney,ChangeTax,SrcPoint")
              .AddInputParameter("@TableName", DbType.String, "Web_VChangeRecord")
              .AddInputParameter("@Wheres", DbType.String, where)
              .AddInputParameter("@KeyName", DbType.String, "ID")
              .AddInputParameter("@OrderBy", DbType.String, "EndTime desc")
              .ToDataSet();

            if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                GameSeachList.Visible = true;
                GameSeachList.DataSource = ds.Tables[1];
                GameSeachList.DataBind();
                NoUserGame.Visible = false;
            }
            else
            {
                this.NoUserGame.Visible = true;
                GameSeachList.Visible = false;
            }

        }
    }
    protected string GetName(object uid)
    {
        if (uid == null)
            return "";
        return DbSession.Default.FromSql("select UserName from TUsers where UserID=" + uid.ToString()).ToScalar().ToString();
    }

    protected void btnSearch_Click(object sender, EventArgs e)
    {
        BindList();
    }

    protected void GameSeachList_ItemDataBound(object sender, RepeaterItemEventArgs e)
    {
        if (e.Item.ItemType == ListItemType.AlternatingItem || e.Item.ItemType == ListItemType.Item)
        {
            DataRowView view = (DataRowView)e.Item.DataItem;
            int id = (int)view["ID"];

            //            string sql = @"select ID,TUsers.UserName,RoomName,DeskIndex,SrcPoint,SrcMoney,ChangePoint,ChangeMoney,ChangeTax from Web_VChangeRecord
            //							inner join TUsers
            //							on Web_VChangeRecord.UserID=TUsers.UserID
            //							where ID=@RecordIndex ";
            string sql = @"select ID,UserID,UserName,RoomName,DeskIndex,SrcPoint,SrcMoney,ChangePoint,ChangeMoney,ChangeTax from Web_VChangeRecord where ID=@RecordIndex ";
            DataTable dt = DbSession.Default.FromSql(sql)
                .AddInputParameter("@RecordIndex", DbType.Int32, id)
                .ToDataTable();
            if (dt.Rows.Count > 0)
            {
                StringBuilder sb = new StringBuilder();
                string tmp = "<a href='UserGameSeachList_xg.aspx?id={0}' title='房间名：{2}&#13;桌号：{3}&#13;结束时总分：{4}&#13;结束时金币：{5}&#13;改变分数：{6}&#13;改变金币：{7}&#13;税：{8}'>{1}</a>&nbsp;&nbsp;&nbsp;&nbsp;";

                foreach (DataRow row in dt.Rows)
                {
                    sb.AppendFormat(
                        tmp,
                        row["ID"].ToString(),
                        row["UserName"].ToString(),
                        row["RoomName"].ToString(),
                        row["DeskIndex"].ToString(),
                        row["SrcPoint"].ToString(),
                        row["SrcMoney"].ToString(),
                        row["ChangePoint"].ToString(),
                        row["ChangeMoney"].ToString(),
                        row["ChangeTax"].ToString()
                        );
                }

                Literal ltinfo = (Literal)e.Item.FindControl("ltRelateUser");
                ltinfo.Text = sb.ToString();
            }
        }
    }
}

