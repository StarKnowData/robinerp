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

public partial class Admin_Users_RookiePresent : AdminBasePage
{
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "04" );

		if( IsPostBack )
			return;

		txtBeginDate.Text = RookiePresentConfig.Config.BeginDate.ToString( "yyyy-MM-dd" );
		txtEndDate.Text = RookiePresentConfig.Config.EndDate.ToString( "yyyy-MM-dd" );
		txtMoney.Text = RookiePresentConfig.Config.Money.ToString();
		cbxIsEnable.Checked = RookiePresentConfig.Config.IsEnable;
		//开始构造动态表单
		//1、读取道具定义表
		DataTable dt = DbSession.Default.FromSql( "select * from TPropDefine" ).ToDataTable();
		//2、循环数据，创建控件并赋值
		HtmlTable table = new HtmlTable();
		table.Border = 1;
		table.Style.Value = "border-collapse:collapse;";
		table.CellPadding = 3;
		table.CellSpacing = 0;
		table.Width = "350";
		foreach( DataRow row in dt.Rows )
		{
			#region 构造动态表单
			HtmlTableRow tr = new HtmlTableRow();
			HtmlTableCell tdPropName = new HtmlTableCell();
			tdPropName.Align = "right";
			tdPropName.InnerText = row["PropName"].ToString() + "：";
			tr.Controls.Add( tdPropName );

			HtmlTableCell tdInput = new HtmlTableCell();
			tdInput.Align = "left";
			tdInput.NoWrap = false;

			HtmlInputText txt = new HtmlInputText();
			txt.ID = "txt_" + row["PropID"].ToString();
			if( RookiePresentConfig.Config.PropPresent.Rows.Count > 0 )
			{
				DataRow[] p = RookiePresentConfig.Config.PropPresent.Select( "PropID=" + row["PropID"].ToString() );
				if( p.Length > 0 )
					txt.Value = p[0]["Amount"].ToString();
				else
					txt.Value = "0";
			}
			else
				txt.Value = "0";
			txt.Attributes.Add( "class", "put imeclose" );
			txt.Attributes.Add( "onkeypress", "return KeyPressNum(this,event);" );

			Literal lt = new Literal();
			lt.Text = "个";

			tdInput.Controls.Add( txt );
			tdInput.Controls.Add( lt );

			tr.Controls.Add( tdInput );

			table.Controls.Add( tr );
			#endregion
		}
		phPropPresent.Controls.Add( table );
	}

	protected void btnSubmit_Click( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;
		RookiePresentConfig model = new RookiePresentConfig();
		model.BeginDate = string.IsNullOrEmpty( txtBeginDate.Text.Trim() ) ? DateTime.Now : DateTime.Parse( txtBeginDate.Text.Trim() );
		model.EndDate = string.IsNullOrEmpty( txtEndDate.Text.Trim() ) ? DateTime.Now : DateTime.Parse( txtEndDate.Text.Trim() );
		model.IsEnable = cbxIsEnable.Checked;
		model.Money = string.IsNullOrEmpty( txtMoney.Text.Trim() ) ? 0 : int.Parse( txtMoney.Text.Trim() );
		//开始读取动态表单内容
		//1、构造表结构
		DataTable dt = new DataTable();
		dt.Columns.Add( new DataColumn( "PropID", typeof( Int32 ) ) );
		dt.Columns.Add( new DataColumn( "Amount", typeof( Int32 ) ) );
		//读取Request
		foreach( string key in Request.Form.AllKeys )
		{
			if( !key.StartsWith( "txt_" ) )
				continue;
			if( !CommonManager.String.IsInteger( Request.Form[key] ) || int.Parse( Request.Form[key] ) <= 0 )
				continue;

			string propid = key.Replace( "txt_", "" );
			int value = int.Parse( Request.Form[key] );

			DataRow nrow = dt.NewRow();
			nrow["PropID"] = propid;
			nrow["Amount"] = value;
			dt.Rows.Add( nrow );
		}
		model.PropPresent = dt;
		RookiePresentConfig.Config = model;

		CommonManager.Web.RegJs( this, "alert('修改成功！');RefreshMe();", false );
	}
}
