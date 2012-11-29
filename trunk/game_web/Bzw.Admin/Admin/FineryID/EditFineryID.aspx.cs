using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using Bzw.Data;
using System.Data;

namespace Bzw.Web.Admin.FineryID
{
	public partial class EditFineryID : AdminBasePage
	{
		public string fineryid = CommonManager.Web.Request( "id", "" );
		protected void Page_Load( object sender, EventArgs e )
		{
			AdminPopedom.IsHoldModel( "14" );
			//string fineryid = HttpContext.Current.Request.QueryString["isd"];
			if( !IsPostBack )
			{
				if( Request.UrlReferrer != null )
					ViewState["UrlReferrer"] = Request.UrlReferrer.ToString();
				BindData();
			}
		}

		protected void Button1_Click( object sender, EventArgs e )
		{
			if(!Utility.Common.IsIntegrity(this.TextBox1.Text.ToString())){
				CommonManager.Web.RegJs(this,"alert('价格只能为整数')",false);
				return;
			}
			string explain = Utility.Common.CutStringUnicode( ExplainTB.Text.ToString(), 20, "" );
			int price= Convert.ToInt32(this.TextBox1.Text.ToString());
			string sql = "update Web_FineryID set Price=@Price,IsSale=@IsSale,IsTop=@IsTop,Explain=@Explain where FineryID=" + fineryid + " ";
			int cout=DbSession.Default.FromSql( sql )
				.AddInputParameter( "@Price", DbType.Int32, price )
				.AddInputParameter( "@IsSale", DbType.Int32, sjRDO.SelectedItem.Value)
				.AddInputParameter( "@IsTop", DbType.Int32, tjRDO.SelectedItem.Value )
				.AddInputParameter("@Explain", DbType.String, explain)
				.Execute();
			if( cout > 0 )
			{
				CommonManager.Web.RegJs( this, "alert('修改成功');", false );
			}
			else
			{
				CommonManager.Web.RegJs( this, "alert('未知错误');", false );
			}
		}

		public void BindData()
		{
			if( string.IsNullOrEmpty( fineryid ) || !CommonManager.String.IsInteger( fineryid ) )
			{
				Alert( "请勿非法操作！", null );
				return;
			}
			string sql = "select Price,IsSale,IsTop,Explain from Web_FineryID where FineryID=" + fineryid + "";
			DataTable tb = DbSession.Default.FromSql( sql ).ToDataTable();
			if( tb.Rows.Count <= 0 )
			{
				CommonManager.Web.RegJs( this, "alert('参数错误!');", false );
				return;
			}
			DataRow row = tb.Rows[0];
			Label1.Text = fineryid;
			TextBox1.Text = row["Price"].ToString();
			ExplainTB.Text = row["Explain"].ToString();
			CommonManager.Web.SetListControlSelectedFromValue( sjRDO, ( Convert.ToInt32( row["IsSale"] ) ).ToString() );
			CommonManager.Web.SetListControlSelectedFromValue( tjRDO, ( Convert.ToInt32( row["IsTop"] ) ).ToString() );
		}

		protected void Button2_Click( object sender, EventArgs e )
		{
			Response.Redirect( ViewState["UrlReferrer"].ToString() );
		}

	}
}
