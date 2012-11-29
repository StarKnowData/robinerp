using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Bzw.Data;
using BCST.Common;
using IpHandle;
using Utility;

public partial class Admin_Books_book : AdminBasePage
{
    public int TableID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("02");
        BatchDelete();
		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "web_msg" )
		   .AddInputParameter( "@Wheres", DbType.String, "" )
		   .AddInputParameter( "@KeyName", DbType.String, "msgid" )
		   .AddInputParameter( "@OrderBy", DbType.String, "msgid desc" )
		   .ToDataSet();
		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			BookList.DataSource = ds.Tables[1];
			BookList.DataBind();
			BookList.Visible = true;
			NoBookList.Visible = false;
		}
		else
		{
			NoBookList.Visible = true;
			BookList.Visible = false;
		}

		/*
        DataTable sd = new DataTable();
        string para = "";
        string[] sql = new string[2];
        sql[0] = "select * from web_msg order by msgid desc";
        sql[1] = "select count(*) from web_msg";
        string url = "";
        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater Vlist = (Repeater)Page.FindControl("BookList");
            Vlist.DataSource = sd;
            Vlist.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            this.NoBookList.Visible = true;
            sd.Clear();*/
    }



    //批量删除
    public void BatchDelete()
    {

        string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "batchdel")
        {


            //批量删除
            //  new BLL.Member().BatchDelete(id);

            DbSession.Default.FromSql("delete from Web_msg where msgid in (" + id + ") ").Execute();

            string descript = "删除玩家留言ID为" + id + "的资料";
            string system = Common.GetOS;
            //管理员操作日志
            new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1);

            Response.Write("<script>alert('温馨提示：\\n\\n批量删除操作成功！');location.href='book.aspx'; </script>");
        }
    }









}
