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

public partial class Admin_News_NewsEtype : AdminBasePage
{
	string EtypeId;
	public string TypeName, TypeSort;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "10" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			EtypeId = tmp;//Limit.editCharacter(Limit.getFormValue("id"));

		DataTable sd = new DataTable();
		string sql = "select * from Web_NewsType Where Typeid=" + EtypeId + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable();
		if( sd.Rows.Count > 0 )
		{
			TypeName = sd.Rows[0]["TypeName"].ToString();
			TypeSort = sd.Rows[0]["TypeSort"].ToString();
		}
		sd.Clear();
	}

	protected void TypeEd( object sender, EventArgs e )
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

		string sql = @"UPDATE [Web_NewsType] SET 
	[TypeName] = @TypeName,[TypeSort] = @TypeSort
	WHERE Typeid=@Typeid ";
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@TypeName", DbType.String, sqlTypeName )
			.AddInputParameter( "@TypeSort", DbType.String, sqlTypeSort )
			.AddInputParameter( "@Typeid", DbType.String, EtypeId )
			.Execute();

		Alert( "新闻分类修改成功！", "NewsType.aspx" );
		
	}
}
