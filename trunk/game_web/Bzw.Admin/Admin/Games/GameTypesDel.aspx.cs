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

public partial class Admin_Games_GameTypesDel :AdminBasePage
{
    string typeids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			typeids = tmp;
		//Limit.editCharacter( Limit.getFormValue( "id" ) );

        string sql = "delete from [TGameKindInfo] Where KindID='" + Convert.ToInt32(typeids) + "'";
		//sqlconn.sqlReader(sql);
		//Limit.outMsgBox("温馨提示：\\n\\n删除成功！", "GameTypes.aspx", true);
		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('删除操作成功！');location.href='GameTypes.aspx';</script>" );
    }
}
