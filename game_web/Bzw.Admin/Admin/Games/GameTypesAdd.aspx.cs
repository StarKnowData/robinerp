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

public partial class Admin_Games_GameTypesAdd : AdminBasePage
{
    public int tableids;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );
       
	}


	protected void GameTypeAdd( object sender, EventArgs e )
	{
		string sqlKindName, sqlIDSort, sqlEnable;
		sqlKindName = CommonManager.Web.RequestForm( "KindName", "" );//Limit.editCharacter(Limit.getFormValue("KindName"));
		if( sqlKindName.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n请输入游戏类别名称！", null );
			return;
		}
		sqlIDSort = CommonManager.Web.RequestForm( "IDSort", "" );//Limit.editCharacter( Limit.getFormValue( "IDSort" ) );
		if (!CommonManager.String.IsInteger (sqlIDSort))
		{
			CommonManager.Web.RegJs(this, "alert('[排列号]必须为数字！');location.href=location.href;", false);
			return ;
		}
		if( sqlIDSort.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n请输入排列号！", null );
			return;
		}
		sqlEnable = CommonManager.Web.RequestForm( "Enable", "" );//Limit.editCharacter( Limit.getFormValue( "Enable" ) );

		int kid = Utility.SqlHelper.GetMaxID( "KindID", "TGameKindInfo" );

        

		string sql = @"INSERT INTO [TGameKindInfo](
	[KindID],[KindName],[IDSort],[Enable]
	)VALUES(
	@KindID,@KindName,@IDSort,@Enable
	)";
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@KindID", DbType.String, kid )
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
                .AddInputParameter("@ParentKindID",DbType.String,kid)
                .Execute();
        }
		Alert( "操作成功！", "GameTypes.aspx" );

		/*
		Hashtable ind = new Hashtable();
		ind.Add( "KindID", kid );
		ind.Add( "KindName", sqlKindName );
		ind.Add( "IDSort", sqlIDSort );
		ind.Add( "Enable", sqlEnable );
		int SqlState = sqlconn.sqlExecute( ind, "[TGameKindInfo]", 1 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n游戏类别添加成功！", "GameTypes.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n游戏类别添加失败！", true );*/
	}
}
