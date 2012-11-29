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
using BCST.Common;
using Bzw.Data;

public partial class Admin_GameInfo_GameMain : AdminBasePage
{
	public int tableids;
	public string typeids;
	string type_ids;
	string sqlW, sqlC;
	string para = "";
	public string sqltitle, sqltype;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		if( !IsPostBack )
		{
			GameInfo();
		}
	}

	protected void GameMainSo( object sender, EventArgs e )
	{
		sqltitle = CommonManager.Web.RequestForm( "title", "" ); //Limit.editCharacter(Limit.getFormValue("title"));
		sqltype = CommonManager.Web.RequestForm( "sotype", "" ); //Limit.editCharacter(Limit.getFormValue("sotype"));
		// Response.Write(sqltitle);
		// Response.Write(sqltype);
		//Response.End();
		Response.Redirect( "GameMain.aspx?sqltitle=" + sqltitle + "&sqltype=" + sqltype + "" );
	}

	protected void GameInfo()
	{
		DataTable sd2 = new DataTable();
        string sql2 = "select * from TGameKindInfo where Enable=1 order by KindID desc";
		sd2 = DbSession.Default.FromSql( sql2 ).ToDataTable(); //sqlconn.sqlReader(sql2);
		if( sd2.Rows.Count > 0 )
		{
			this.sotype.DataBind();
			for( int i = 0; i < sd2.Rows.Count; i++ )
			{
                this.sotype.Items.Add(new ListItem(sd2.Rows[i]["KindName"].ToString(), sd2.Rows[i]["KindID"].ToString()));
			}

			GameTypeList.DataSource = sd2;
			GameTypeList.DataBind();
		}
		else
			this.NoGameMainList.Visible = true;
		sd2.Clear();

		typeids = CommonManager.Web.Request( "type", "" );//Limit.editCharacter( Limit.getFormValue( "type" ) );
		if( typeids.ToString() == "" )
			typeids = "1";
		type_ids = CommonManager.Web.Request( "sid", "" );//Limit.editCharacter(Limit.getFormValue("sid"));

		if( typeids.ToString() == "1" )
		{
			sqlW = " and through=" + typeids + "";
			// Response.Write(sqlW);
			sqlC = " and through=" + typeids + "";
			para = "type=" + typeids;
		}
		else if( typeids.ToString() == "0" )
		{
			sqlW = " and through=" + typeids + "";
			//Response.Write(sqlW);
			sqlC = " and through=" + typeids + "";
			para = "type=" + typeids;
		}

		sqltitle = CommonManager.Web.Request( "sqltitle", "" );//Limit.editCharacter( Limit.getFormValue( "sqltitle" ) );
		sqltype = CommonManager.Web.Request( "sqltype", "" );//Limit.editCharacter( Limit.getFormValue( "sqltype" ) );
		//Response.Write(sqltitle);
		//Response.Write(sqltype);
		//Response.End();
		if( typeids.ToString() != "" && type_ids.ToString() != "" )
		{
			sqlW = " and Game_Typeid=" + type_ids + " and through=" + typeids + "";
			//Response.Write(sqlW);
			sqlC = " and Game_Typeid=" + type_ids + " and through=" + typeids + "";
			para = "type=" + typeids + "&id=" + type_ids;
		}

		if( sqltitle.ToString() != "" && sqltype.ToString() != "" )
		{
			sqlW = " and Game_Typeid=" + sqltype + " and Game_Name like '%" + sqltitle + "%'";
			sqlC = " and Game_Typeid=" + sqltype + " and Game_Name like '%" + sqltitle + "%'";
			para = "t=" + sqltype + "&=" + sqltitle + "";
		}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "web_gameinfo" )
		   .AddInputParameter( "@Wheres", DbType.String, sqlW )
		   .AddInputParameter( "@KeyName", DbType.String, "game_id" )
		   .AddInputParameter( "@OrderBy", DbType.String, "game_id desc" )
		   .ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			GameMainList.DataSource = ds.Tables[1];
			GameMainList.DataBind();
			GameMainList.Visible = true;
			NoGameMainList.Visible = false;
		}
		else
		{
			NoGameMainList.Visible = true;
			GameMainList.Visible = false;
		}

		/*
		DataTable sd = new DataTable();
		string[] sql = new string[2];
		sql[0] = "select * from web_gameinfo " + sqlW + " order by game_id desc";
		//Response.Write(sql[0]);
		sql[1] = "select count(*) from web_gameinfo " + sqlC + "";
		string url = "GameMain.aspx";
		PageLink page_set = new PageLink( url, 20, 10, para, sql );
		page_set.paraLinkType = paraLinkShow.middling.ToString();
		sd = page_set.get_table();
		if( sd.Rows.Count > 0 )
		{
			Repeater Vista = (Repeater)Page.FindControl( "GameMainList" );
			Vista.DataSource = sd;
			Vista.DataBind();
			this.pageList.Text = page_set.pageList();
		}
		else
			this.NoGameMainList.Visible = true;
		sd.Clear();*/
	}
}
