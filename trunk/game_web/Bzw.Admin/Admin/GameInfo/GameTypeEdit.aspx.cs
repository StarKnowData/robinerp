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

public partial class Admin_GameInfo_GameTypeEdit : AdminBasePage
{
	string typeid;
	public string TypeName, TypeSort;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');", false );
			return;
		}
		else
			typeid = tmp; //Limit.editCharacter(Limit.getFormValue("id"));

		DataTable sd = new DataTable();
		string sql = "select * from web_GameType where typeid =" + typeid + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
		if( sd.Rows.Count > 0 )
		{
			this.TypeName = sd.Rows[0]["TypeName"].ToString();
			this.TypeSort = sd.Rows[0]["TypeSort"].ToString();
		}
		sd.Clear();
	}

	protected void TypeEdit( object sender, EventArgs e )
	{
		string sqlTypeName, sqlTypeSort;

		sqlTypeName = CommonManager.Web.RequestForm( "TypeName", "" ); //Limit.editCharacter( Limit.getFormValue( "TypeName" ) );
		if( sqlTypeName.ToString() == "" )
		{
			CommonManager.Web.RegJs( this, "alert('分类名称不能为空！');", false );
			return;
		}
		sqlTypeSort = CommonManager.Web.RequestForm( "TypeSort", "" ); //Limit.editCharacter( Limit.getFormValue( "TypeSort" ) );
		if (!CommonManager.String.IsInteger(sqlTypeSort))
		{
			CommonManager.Web.RegJs(this, "alert('[分类排序]必须为数字！');location.href=location.href;", false);
			return;
		}
		string sql = @"update web_GameType set TypeName=@TypeName,TypeSort=@TypeSort where Typeid=@Typeid";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@TypeName", DbType.String, sqlTypeName )
			.AddInputParameter( "@TypeSort", DbType.String, sqlTypeSort )
			.AddInputParameter( "@Typeid", DbType.String, typeid )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='GameType.aspx';", false );
/*
		Hashtable ind = new Hashtable();
		//ind.Add("TypeID", Convert.ToInt32(typeid) + Convert.ToInt32(1));
		ind.Add( "TypeName", sqlTypeName );
		ind.Add( "TypeSort", sqlTypeSort );
		int SqlState = sqlconn.sqlExecute( ind, "[web_GameType]", "Typeid=" + typeid + "", 2 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n游戏分类修改成功！", "GameType.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n游戏分类修改失败！", true );*/
	}
}
