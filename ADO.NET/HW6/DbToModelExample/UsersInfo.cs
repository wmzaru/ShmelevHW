//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace EmailClient
{
    using System;
    using System.Collections.Generic;
    
    public partial class UsersInfo
    {
        public long Id { get; set; }
        public string LastName { get; set; }
        public string FirstName { get; set; }
        public string Adres { get; set; }
        public string Phone { get; set; }
        public Nullable<int> Code { get; set; }
        public Nullable<long> UserId { get; set; }
    
        public virtual User User { get; set; }
    }
}
