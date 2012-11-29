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

public partial class Admin_GameInfo_GameType_Add : AdminBasePage
{
	string typeid;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		DataTable sd = new DataTable();
		string sql = "select max (typeid) as typeid from web_gametype";
		sd = DbSession.Default.FromSql( sql ).ToDataTable();
		//sqlconn.sqlReader( sql );
		if( sd.Rows.Count > 0 )
		{
			typeid = sd.Rows[0]["typeid"].ToString();
			if( typeid.ToString() == "" )
				typeid = "0";
		}
		sd.Clear();
	}

	protected void TypeAdd( object sender, EventArgs e )
	{
		string sqlTypeName, sqlTypeSort;
		sqlTypeName = CommonManager.Web.RequestForm( "TypeName", "" ); //Limit.editCharacter( Limit.getFormValue( "TypeName" ) );
		if( sqlTypeName.ToString() == "" )
		{
			//Limit.outMsgBox( "温馨提示：\\n\\n 分类名称不能为空！", true );
			CommonManager.Web.RegJs( this, "alert('分类名称不能为空！');", false );
			return;
		}
		sqlTypeSort = CommonManager.Web.RequestForm( "TypeSort", "" ); //Limit.editCharacter( Limit.getFormValue( "TypeSort" ) );
		if (!CommonManager.String.IsInteger(sqlTypeSort))
		{
			CommonManager.Web.RegJs(this, "alert('[分类排序]必须为数字！');location.href=location.href;", false);
			return;
		}

		string sql = @"insert web_GameType (TypeName,TypeSort) values (@TypeName,@TypeSort)";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@TypeName", DbType.String, sqlTypeName )
			.AddInputParameter( "@TypeSort", DbType.String, sqlTypeSort )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='GameType.aspx';", false );

		/*
		Hashtable ind = new Hashtable();
		//ind.Add("TypeID", Convert.ToInt32(typeid) + Convert.ToInt32(1));
		ind.Add( "TypeName", sqlTypeName );
		ind.Add( "TypeSort", sqlTypeSort );
		int SqlState = sqlconn.sqlExecute( ind, "[web_GameType]", 1 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n游戏分类添加成功！", "GameType.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n游戏分类添加失败！", true );*/
	}
}
