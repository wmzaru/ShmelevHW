//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace BankApplication
{
    using System;
    using System.Collections.Generic;
    
    public partial class BankBranch
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public BankBranch()
        {
            this.ReviewsSet = new HashSet<Reviews>();
            this.ServicesSet = new HashSet<Services>();
        }
    
        public int Id { get; set; }
        public string Name { get; set; }
        public string PhoneNumber { get; set; }
        public string Address { get; set; }
        public double Xpos { get; set; }
        public double Ypos { get; set; }
        public Nullable<System.DateTime> OpenDate { get; set; }
        public string WorkTime { get; set; }
        public string BreakTime { get; set; }
        public int Bank_Id { get; set; }
        public string OperatorInfo { get; set; }
    
        public virtual Bank BankSet { get; set; }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<Reviews> ReviewsSet { get; set; }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<Services> ServicesSet { get; set; }
    }
}
