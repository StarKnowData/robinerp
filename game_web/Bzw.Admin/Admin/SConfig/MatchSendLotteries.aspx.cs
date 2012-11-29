using System;
using System.Data;

using Bzw.Data;
using BCST.Common;
using System.Web.UI.WebControls;

public partial class Admin_SConfig_MatchSendLotteries : AdminBasePage
{
	//获取房间配置表TMatchRoomManage的主键ID号
	protected void Page_Load( object sender, EventArgs e )
	{
        AdminPopedom.IsHoldModel("18");

		if( !IsPostBack )
		{ 
            BindList();
		}

		string action = CommonManager.Web.Request( "action", "" );
		if( string.IsNullOrEmpty( action ) )
			return;
		switch( action )
		{
			case "edit":
				EditInfo();
				break;
			case "del":
				DelInfo();
				return;
			default:
				break;
		}
	}
  
    private void BindList()
    {
        string where = "";
        if (Request.QueryString["type"] != null && Request.QueryString["type"] != "")
        {
            where = " and typeid="+Request.QueryString["type"];
        }
        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                    .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                    .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                    .AddInputParameter("@Columns", DbType.String, "*")
                    .AddInputParameter("@TableName", DbType.String, "Web_vMatchAwardConfig")
                    .AddInputParameter("@Wheres", DbType.String, where)
                    .AddInputParameter("@KeyName", DbType.String, "ID")
                    .AddInputParameter("@OrderBy", DbType.String, "Rank ASC")
                    .ToDataSet();

        if (ds.Tables.Count > 0)
        {
            anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
            anpPageIndex.CurrentPageIndex = PageIndex;

            if (ds.Tables[1].Rows.Count > 0)
            {
                rptDataList.Visible = true;
                ltNonData.Visible = false;
                rptDataList.DataSource = ds.Tables[1];
                rptDataList.DataBind();
            }
            else
            {
                rptDataList.Visible = false;
                ltNonData.Visible = true;
            }
        }
        DataTable dt = DbSession.Default.FromSql("select * from Web_MatchSendType").ToDataTable();
        if (dt.Rows.Count > 0)
        {
            ddlMethod.DataBind();
            ddlMethod.Items.Clear();
            ddlSmethod.DataBind();
            ddlSmethod.Items.Clear();
            ddlSmethod.Items.Add(new ListItem("请选择方案名", ""));
            foreach (DataRow dr in dt.Rows)
            {
                ddlSmethod.Items.Add(new ListItem(dr["Name"].ToString(), dr["ID"].ToString()));
                ddlMethod.Items.Add(new ListItem(dr["Name"].ToString(), dr["ID"].ToString()));
            }

            if (Request.QueryString["type"] != null && Request.QueryString["type"] != "")
            {
                ddlSmethod.SelectedValue = Request.QueryString["type"];

            }
        }
    }
	private void DelInfo()
	{
		 
		string aid = CommonManager.Web.Request( "params", "" );
		if( !CommonManager.String.IsInteger( aid ) )
			return;
		DbSession.Default.FromSql( "delete Web_MatchAwardConfig where ID=" + aid ).Execute();
        CommonManager.Web.RegJs(this, "alert('刪除成功！');location.href='MatchSendLotteries.aspx';", true);
	}

	private void EditInfo()
	{
		 
		string aid = CommonManager.Web.Request( "params", "" );
		if( IsPostBack || !CommonManager.String.IsInteger( aid ) )
			return;
		DataTable dt = DbSession.Default.FromSql( "select * from Web_MatchAwardConfig where ID=" + aid ).ToDataTable();
		if( dt.Rows.Count <= 0 || IsPostBack )
			return;
		DataRow row = dt.Rows[0];
		txtGiveNum.Text = row["GiveNum"].ToString();
		txtRank.Text = row["Rank"].ToString();
	
		ddlMethod.SelectedValue=row["TypeID"].ToString();
		btnSubmit.Text = " 修 改 ";
	}
	protected void btnSubmit_Click( object sender, EventArgs e )
	{

		if( !CommonManager.Web.CheckPostSource() )
			return;
		if( !IsValid )
			return;

		string ID = CommonManager.Web.Request( "params", "0" );

		string type = CommonManager.Web.RequestForm( "ddAwardName","" );
		string sql = "";
        string reurl = CommonManager.Web.RequestHtmlDecode("reurl", "");
        string location = string.Empty;
        if (!string.IsNullOrEmpty(location))
            location = reurl;
        else
            location = Request.Url.AbsoluteUri;
		if( !CommonManager.String.IsInteger( ID ) || int.Parse( ID ) <= 0 )
		{
			 
            if (Convert.ToInt32(DbSession.Default.FromSql("select count(0) from Web_MatchAwardConfig where typeid=" + ddlMethod.SelectedValue + " and Rank=" + txtRank.Text.Trim()).ToScalar()) == 0)
            {

                sql = "insert into Web_MatchAwardConfig (Rank,GiveNum,TypeID) values (@Rank,@GiveNum,@TypeID)";

                DbSession.Default.FromSql(sql)
                    .AddInputParameter("@Rank", DbType.Int32, txtRank.Text.Trim())
                    .AddInputParameter("@GiveNum", DbType.Int32, txtGiveNum.Text.Trim()) 
                    .AddInputParameter("@TypeID", DbType.Int32, ddlMethod.SelectedValue)
                    .Execute();
            }
            else
            {
                CommonManager.Web.RegJs(this.Page, "alert('对不起，此名次已添加！');location.href='MatchSendLotteries.aspx';", true);
                return;
            }
		}
		else
		{
			sql = "update Web_MatchAwardConfig set Rank=@Rank,GiveNum=@GiveNum where ID=@ID";

            DbSession.Default.FromSql(sql)
                .AddInputParameter("@Rank", DbType.Int32, txtRank.Text.Trim())
                .AddInputParameter("@GiveNum", DbType.Int32, txtGiveNum.Text.Trim())
               
                .AddInputParameter("@ID", DbType.Int32, ID)
                .Execute();
		}




        CommonManager.Web.RegJs(this.Page, "alert('操作成功！');location.href='MatchSendLotteries.aspx';", true);
	}

     
}
