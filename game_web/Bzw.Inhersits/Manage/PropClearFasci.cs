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
using System.Collections.Generic;
using Bzw.Data;
using BCST.Common;

namespace Bzw.Inhersits.Manage
{
public partial class Manage_PropClearFasci : UiCommon.ManageBasePage
{
    /// <summary>
    /// webmeta1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webmeta1;

    /// <summary>
    /// webtop1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webtop1;

    /// <summary>
    /// Left1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl Left1;

    /// <summary>
    /// webuserlogin1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webuserlogin1;

    /// <summary>
    /// form1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.HtmlControls.HtmlForm form1;

    /// <summary>
    /// ddlType 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.WebControls.DropDownList ddlType;

    /// <summary>
    /// lblMsg 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.WebControls.Label lblMsg;

    /// <summary>
    /// button5 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.HtmlControls.HtmlInputSubmit button5;

    /// <summary>
    /// rptList 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.WebControls.Repeater rptList;

    /// <summary>
    /// webfooter1 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.UserControl webfooter1;
	public int UserFasci
	{
		get
		{
			if( ViewState["UserFascis"] == null )
			{
				return new BLL.Member().GetUserFasci( UiCommon.UserLoginInfo.UserID );
			}
			else
			{
				return Convert.ToInt32( ViewState["UserFascis"] );
			}
		}
		set
		{

			ViewState["UserFascis"] = value;

		}
	}
	protected void Page_Load( object sender, EventArgs e )
	{
		if( !IsPostBack )
		{
			BindPropFasci();
		}
	}
	public void BindPropFasci()
	{
		UserFasci = new BLL.Member().GetUserFasci( UiCommon.UserLoginInfo.UserID );
		DataTable dt = new BLL.DaoJu().GetInfoOfPropFasci();
		if( dt != null )
		{
			this.ddlType.Items.Clear();
			for( int i = 0; i < dt.Rows.Count; i++ )
			{
				this.ddlType.Items.Add( new ListItem( dt.Rows[i]["Title"].ToString(), dt.Rows[i]["ID"].ToString() ) );
			}

			rptList.DataSource = dt;
			rptList.DataBind();
		}
	}

	protected void button5_ServerClick( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
		{
			return;
		}
		int pPrice = 0, pFasci = 0;
		int clearFasci = 0, afterFasci = 0;
		if( UserFasci >= 0 )
		{
			lblMsg.Text = "只有魅力值小于零时，才可以购买并使用此道具！";
			return;
		}
		int iPropID = Convert.ToInt32( ddlType.SelectedValue );//道具ID号
		DataRow dr = new BLL.DaoJu().GetPropFasciForID( iPropID );
		if( dr != null )
		{
			pPrice = Convert.ToInt32( dr["Price"].ToString() );// 道具价格
			pFasci = Convert.ToInt32( dr["DecFasci"].ToString() );//道具能清除的魅力点数
		}

		//判断银行的钱是否足够
		Int64 bankMoney = new BLL.Member().GetBankMoney( UiCommon.UserLoginInfo.UserID );
		if( bankMoney < pPrice )
		{
            lblMsg.Text = "您银行中的" + UiCommon.StringConfig.MoneyName + "不足，请充值后再购买！";
			return;
		}

		int iLeaveFasci = UserFasci + pFasci;

		if( iLeaveFasci <= 0 )
		{
			clearFasci = pFasci;//已清掉的魅力值点数
			afterFasci = iLeaveFasci;
		}
		else
		{
			clearFasci = pFasci - iLeaveFasci;//已清掉的魅力值点数
			afterFasci = 0;
		}

		//int iRows = new BLL.Member().BuyPropFasci( UiCommon.UserLoginInfo.UserID, iPropID, pPrice, clearFasci, UserFasci, afterFasci );
		Dictionary<string, object> dic = new Dictionary<string, object>();
		DbSession.Default.FromProc( "Web_pClearFasciPropBuyLog" )
			.AddInputParameter( "@UserID", DbType.String, UiCommon.UserLoginInfo.UserID )
			.AddInputParameter( "@FasciPropID", DbType.String, iPropID )
			.AddReturnValueParameter( "@ReturnValue", DbType.Int32 )
			.Execute( out dic );
		if( dic.Count > 0 )
		{
			string mgs = "";
			switch( (int)dic["ReturnValue"] )
			{
				case 1:
					mgs = "使用成功！您已经清零了" + clearFasci + "点魅力值。";
					break;
				case -9:
					mgs = "抱歉，参数有误！";
					break;
				case -8:
					mgs = "抱歉，用户不存在！";
					break;
				case -7:
					mgs = "抱歉，该清零道具不存在！";
					break;
				case -6:
					mgs = "抱歉，魅力值必须是小于零才能够执行清零操作！";
					break;
				default:
					mgs = "抱歉，操作失败，可能服务器忙，请稍候再试！";
					break;				
			}
			CommonManager.Web.RegJs( this, "alert('" + mgs + "');location.href=location.href;", true );
		}
		else
		{
			CommonManager.Web.RegJs( this, "alert('抱歉，操作失败，可能服务器忙，请稍候再试！');location.href=location.href;", true );
		}

	}
}
}
