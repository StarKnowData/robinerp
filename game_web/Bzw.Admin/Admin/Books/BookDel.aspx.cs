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
public partial class Admin_Books_BookDel : AdminBasePage
{
	string BookID;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "02" );

		string tmp = CommonManager.Web.Request( "id", "" );

		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');", false );
			return;
		}
		else
			BookID = tmp; //Limit.editCharacter( Limit.getFormValue( "id" ) );

		string sql = "delete from web_msg where Msgid =" + BookID + "";

		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('留言删除成功！');location.href='book.aspx';</script>" );
	}
}
