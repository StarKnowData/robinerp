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

public partial class Admin_Trans_TransDel : AdminBasePage
{
    string transid;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("08");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			transid = tmp; //Limit.editCharacter(Limit.getFormValue("id"));
        string sql = "delete from Web_TransLog where id=" + transid + "";
		//sqlcon.sqlReader(sql);
		//Limit.outMsgBox("温馨提示：\\n\\n删除操作执行成功！", "Trans.aspx", true);

		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('温馨提示：\\n\\n删除操作成功！');location.href='Trans.aspx';</script>" );
    }
}
