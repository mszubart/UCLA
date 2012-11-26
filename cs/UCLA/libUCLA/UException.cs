using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace libUCLA
{
    /// <summary>
    /// This exception is being thrown when sometginh goes wrong in libxs.
    /// For best debugging, you should check inner exception.
    /// </summary>
    [Serializable]
    public class UException : Exception
    {
        public UException() : base() { }
        public UException(string message) : base(message) { }
        public UException(string message, Exception innerException) : base(message, innerException) { }
    }
}
