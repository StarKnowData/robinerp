using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;
using System.Xml;

 
    public partial class Admin_Lotter_PrList : AdminBasePage
    {
        public int TableID;
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
            if (!IsPostBack)
            {
                if (Request.QueryString["id"] != null && Request.QueryString["id"] != "")
                {
                    DelePr();
                }
                else
                {
                    BindList();
                }
            }
        }
        private void BindList()
        {
            DataTable dt = DbSession.Default.FromSql("select * from Web_LotterAward").ToDataTable();
            PrAdlist.DataSource = dt;
            PrAdlist.DataBind();
        }
        private void DelePr()
        {
            string id = Request.QueryString["id"];
            DbSession.Default.FromSql("delete from Web_LotterAward where id=" + id).Execute();
            string xmlPath = Server.MapPath("/upload/xml/Lotter.xml");
            if (!System.IO.File.Exists(xmlPath))
            {
                CommonManager.Web.RegJs(this, "alert('奖品删除失败，Lotter.xml文件不存在！');history.back();", false);

            }

            try
            {
                XmlDocument xml = new XmlDocument();
                xml.Load(xmlPath);
               
                XmlNode node = xml.SelectSingleNode("//item[@id='" + id + "']");

                XmlNode parent = node.ParentNode;
                parent.RemoveChild(node);
                xml.Save(xmlPath);

                Response.Write("<script>alert('奖品删除成功！');location.href='PrList.aspx';</script>");
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('奖品删除失败！" + ex.Message + "');location.href='PrList.aspx';</script>");

            }
            CommonManager.Web.RegJs(this, "alert('操作成功！');", false);
        }
    }

 
