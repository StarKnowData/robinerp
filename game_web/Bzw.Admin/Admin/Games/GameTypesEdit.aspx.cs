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

public partial class Admin_Games_GameTypesEdit : AdminBasePage
{
	string typeids;
	public string KindName, KindID, IDSort, Enable,ParentKindId;
    public int tableids;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			typeids = tmp; //Limit.editCharacter( Limit.getFormValue( "id" ) );

		DataTable sd = new DataTable();
		string sql = "select * from TGameKindInfo where kindid=" + typeids + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable();
		if( sd.Rows.Count > 0 )
		{
			KindID = sd.Rows[0]["KindID"].ToString();
			KindName = sd.Rows[0]["KindName"].ToString();
			IDSort = sd.Rows[0]["IDSort"].ToString();
			Enable = sd.Rows[0]["Enable"].ToString();
            ParentKindId = sd.Rows[0]["ParentKindID"].ToString();
		}
		else
			Alert( "温馨提示：此记录已不存在！", null );
        GateNames(typeids);
        GetGameKindChild(typeids);
	}

	protected void GameTypeEdit( object sender, EventArgs e )
	{
		string sqlKindName, sqlKindID, sqlIDSort, sqlEnable;
		sqlKindName = CommonManager.Web.RequestForm( "KindName", "" );//Limit.editCharacter( Limit.getFormValue( "KindName" ) );
		if( sqlKindName.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n请输入游戏类别名称！", null );
			return;
		}
		sqlKindID = CommonManager.Web.RequestForm( "KindID", "" );//Limit.editCharacter( Limit.getFormValue( "KindID" ) );
		if( sqlKindID.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n请输入类别号！", null );
			return;
		}
		sqlIDSort = CommonManager.Web.RequestForm( "IDSort", "" );//Limit.editCharacter( Limit.getFormValue( "IDSort" ) );
		if (!CommonManager.String.IsInteger(sqlIDSort))
		{
			CommonManager.Web.RegJs(this, "alert('[排列号]必须为数字！');location.href=location.href;", false);
			return;
		}
		if( sqlIDSort.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n请输入排列号！", null );
			return;
		}
		sqlEnable = CommonManager.Web.RequestForm( "Enable", "" );//Limit.editCharacter( Limit.getFormValue( "Enable" ) );

		string sql = @"UPDATE [TGameKindInfo] SET 
	[KindName] = @KindName,[IDSort] = @IDSort,[Enable] = @Enable
	WHERE KindID=@KindID ";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@KindID", DbType.String, typeids )
			.AddInputParameter( "@KindName", DbType.String, sqlKindName )
			.AddInputParameter( "@IDSort", DbType.String, sqlIDSort )
			.AddInputParameter( "@Enable", DbType.String, sqlEnable )
			.Execute();
        if (CommonManager.Web.RequestForm("KindName2", "") != "")
        {
            int kid2 = Utility.SqlHelper.GetMaxID("KindID", "TGameKindInfo");
            string sqlKindName2 = CommonManager.Web.RequestForm("KindName2", "");
            string sqlIDSort2 = CommonManager.Web.RequestForm("IDSort2", "");
            string sqlEnable2 = CommonManager.Web.RequestForm("Enable2", "");
            string sql2 = @"INSERT INTO [TGameKindInfo](
	[KindID],[KindName],[IDSort],[Enable],[ParentKindID]
	)VALUES(
	@KindID,@KindName,@IDSort,@Enable,@ParentKindID
	)";
            DbSession.Default.FromSql(sql2)
                .AddInputParameter("@KindID", DbType.String, kid2)
                .AddInputParameter("@KindName", DbType.String, sqlKindName2)
                .AddInputParameter("@IDSort", DbType.String, sqlIDSort2)
                .AddInputParameter("@Enable", DbType.String, sqlEnable2)
                .AddInputParameter("@ParentKindID", DbType.String, sqlKindID)
                .Execute();
        }
		Alert( "操作成功！", "GameTypes.aspx" );

		/*
		Hashtable ind = new Hashtable();
		ind.Add( "KindID", sqlKindID );
		ind.Add( "KindName", sqlKindName );
		ind.Add( "IDSort", sqlIDSort );
		ind.Add( "Enable", sqlEnable );
		int SqlState = sqlconn.sqlExecute( ind, "[TGameKindInfo]", "KindID=" + typeids + "", 2 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n游戏类别添加成功！", "GameTypes.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n游戏类别添加失败！", true );*/
	}
   /// <summary> 
   /// </summary>
    protected void GateNames(string typeids)
    {
        AdminPopedom.IsHoldModel("06");

        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
           .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
           .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
           .AddInputParameter("@Columns", DbType.String, "*")
           .AddInputParameter("@TableName", DbType.String, "Web_VGameNameInfo")
           .AddInputParameter("@Wheres", DbType.String, " and kindid=" + typeids + " or ParentKindID="+typeids)
           .AddInputParameter("@KeyName", DbType.String, "NameID")
           .AddInputParameter("@OrderBy", DbType.String, "IDSort desc")
           .ToDataSet();

        if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
        {
            anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
            anpPageIndex.CurrentPageIndex = PageIndex;

            GameNamesList.DataSource = ds.Tables[1];
            GameNamesList.DataBind();
            GameNamesList.Visible = true;
        }
        else
        {
            GameNamesList.Visible = false;
        }
    }
    protected void GetGameKindChild(string typeids)
    {
        AdminPopedom.IsHoldModel("06");
        DataTable sd = new DataTable();
        string sql = "select * from Web_VGameKindList where ParentKindID=" + typeids;
        sd = DbSession.Default.FromSql(sql).ToDataTable();
        if (sd.Rows.Count > 0)
        {
            GameTypesList.DataSource = sd;
            GameTypesList.DataBind();
            GameTypesList.Visible = true;
        }
        else
        {
            GameTypesList.Visible = false;
            
        }
    }
}
