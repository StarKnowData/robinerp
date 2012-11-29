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

public partial class Admin_News_NewsTypeAdd : AdminBasePage
{
	string TypeID;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "10" );

		DataTable sd = new DataTable();
		string sql = "select max(typeid) as typeid from Web_NewsType";
		sd = DbSession.Default.FromSql( sql ).ToDataTable();
		if( sd.Rows.Count > 0 )
		{
			TypeID = sd.Rows[0]["typeid"].ToString();
			if( TypeID.ToString() == "" )
				TypeID = "0";
		}
		sd.Clear();
	}

	protected void TypeAd( object sender, EventArgs e )
	{
		string sqlTypeName, sqlTypeSort;
		sqlTypeName = CommonManager.Web.RequestForm( "TypeName", "" );
		if (string.IsNullOrEmpty(sqlTypeName))
		{
			CommonManager.Web.RegJs(this, "alert('[类别名称]不能为空！');location.href=location.href;", false);
			return;
		}
		sqlTypeSort = CommonManager.Web.RequestForm( "TypeSort", "" );
		if (!CommonManager.String.IsInteger(sqlTypeSort))
		{
			CommonManager.Web.RegJs(this, "alert('[排列号]必须为数字！');location.href=location.href;", false);
			return;
		}
		string sql = @"INSERT INTO [Web_NewsType](
	[TypeName],[TypeSort]
	)VALUES(
	@TypeName,@TypeSort
	)";
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@TypeName", DbType.String, sqlTypeName )
			.AddInputParameter( "@TypeSort", DbType.String, sqlTypeSort )
			.Execute();

		Alert( "新闻分类添加成功！", "NewsType.aspx" );

		/*
		Hashtable ind = new Hashtable();
		//ind.Add("typeid", Convert.ToInt32(TypeID) + Convert.ToInt32(1));
		ind.Add( "TypeName", sqlTypeName );
		ind.Add( "TypeSort", sqlTypeSort );
		int SqlState = sqlconn.sqlExecute( ind, "[Web_NewsType]", 1 );
		ind.Clear();

		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n新闻分类添加成功！", "NewsType.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n新闻分类添加失败！", true );*/
	}
}
