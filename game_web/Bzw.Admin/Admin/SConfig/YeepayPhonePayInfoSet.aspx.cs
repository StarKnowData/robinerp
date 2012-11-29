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

public partial class Admin_SConfig_YeepayPhonePayInfoSet : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
	{
		if( !IsPostBack )
		{
			fckContent.Value = DbSession.Default.FromSql( "select top 1 YeepayMsgInfo from Web_Config" ).ToScalar().ToString();
		}
    }


	protected void Button1_Click( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;

		DbSession.Default.FromSql( "update web_config set YeepayMsgInfo=@YeepayMsgInfo" ).AddInputParameter( "@YeepayMsgInfo", DbType.String, fckContent.Value ).Execute();

		CommonManager.Web.RegJs( this, "alert('修改成功！');location.href=location.href;", false );
	}
}
