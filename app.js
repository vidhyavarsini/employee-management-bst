const STORAGE_KEY="peopledesk-employees-v1";
const starterEmployees=[
{id:1001,name:"Asha Kumar",department:"Human Resources",salary:38000},
{id:1002,name:"Rahul Nair",department:"Engineering",salary:52000},
{id:1003,name:"Meera Iyer",department:"Finance",salary:45000},
{id:1004,name:"Arun Das",department:"Engineering",salary:48000},
{id:1005,name:"Priya Shah",department:"Marketing",salary:41000}
];
let employees=loadEmployees(),editingId=null;
const $=id=>document.getElementById(id);
const money=n=>new Intl.NumberFormat("en-IN",{style:"currency",currency:"INR",maximumFractionDigits:2}).format(n);
function loadEmployees(){try{const s=localStorage.getItem(STORAGE_KEY);return s?JSON.parse(s):starterEmployees.map(e=>({...e}));}catch{return starterEmployees.map(e=>({...e}));}}
function saveEmployees(){localStorage.setItem(STORAGE_KEY,JSON.stringify(employees));}
function escapeHTML(v){return String(v).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));}
function render(){
 const query=$("search").value.trim().toLowerCase(),selected=$("departmentFilter").value;
 const departments=[...new Set(employees.map(e=>e.department))].sort((a,b)=>a.localeCompare(b));
 $("departmentFilter").innerHTML='<option value="all">All departments</option>'+departments.map(d=>`<option value="${escapeHTML(d)}">${escapeHTML(d)}</option>`).join("");
 $("departmentFilter").value=departments.includes(selected)?selected:"all";
 const visible=[...employees].sort((a,b)=>a.id-b.id).filter(e=>(e.name.toLowerCase().includes(query)||e.department.toLowerCase().includes(query)||String(e.id).includes(query))&&($("departmentFilter").value==="all"||e.department===$("departmentFilter").value));
 const payroll=employees.reduce((s,e)=>s+e.salary,0);
 $("totalEmployees").textContent=employees.length;$("totalDepartments").textContent=departments.length;
 $("totalPayroll").textContent=money(payroll);$("averageSalary").textContent=money(employees.length?payroll/employees.length:0);
 $("employeeRows").innerHTML=visible.map(e=>{const initials=e.name.trim().split(/\s+/).slice(0,2).map(s=>s[0]).join("").toUpperCase();return `<tr><td><div class="person-cell"><span class="person-icon">${escapeHTML(initials)}</span><div><strong>${escapeHTML(e.name)}</strong><small>Team member</small></div></div></td><td class="id">#${e.id}</td><td><span class="dept">${escapeHTML(e.department)}</span></td><td class="salary">${money(e.salary)}</td><td><div class="actions"><button class="action" data-edit="${e.id}">Edit</button><button class="action delete" data-delete="${e.id}">Delete</button></div></td></tr>`;}).join("");
 $("empty").classList.toggle("hidden",visible.length>0);$("resultCount").textContent=`Showing ${visible.length} of ${employees.length} employees`;
}
function toast(msg){const t=$("toast");t.textContent=msg;t.classList.add("show");clearTimeout(toast.timer);toast.timer=setTimeout(()=>t.classList.remove("show"),2400);}
function openAdd(){editingId=null;$("employeeForm").reset();$("modalTitle").textContent="Add an employee";$("eid").disabled=false;$("formError").textContent="";$("employeeDialog").showModal();$("name").focus();}
function openEdit(id){const e=employees.find(x=>x.id===id);if(!e)return;editingId=id;$("modalTitle").textContent="Edit employee";$("name").value=e.name;$("eid").value=e.id;$("eid").disabled=true;$("department").value=e.department;$("salary").value=e.salary;$("formError").textContent="";$("employeeDialog").showModal();}
$("addTop").addEventListener("click",openAdd);
$("closeDialog").addEventListener("click",()=>$("employeeDialog").close());
$("cancelDialog").addEventListener("click",()=>$("employeeDialog").close());
$("search").addEventListener("input",render);$("departmentFilter").addEventListener("change",render);
$("employeeRows").addEventListener("click",ev=>{
 const edit=ev.target.closest("[data-edit]"),del=ev.target.closest("[data-delete]");
 if(edit)openEdit(Number(edit.dataset.edit));
 if(del){const id=Number(del.dataset.delete),e=employees.find(x=>x.id===id);if(e&&confirm(`Delete ${e.name}'s record?`)){employees=employees.filter(x=>x.id!==id);saveEmployees();render();toast("Employee deleted");}}
});
$("employeeForm").addEventListener("submit",ev=>{
 ev.preventDefault();const name=$("name").value.trim(),id=Number($("eid").value),department=$("department").value.trim(),salary=Number($("salary").value);
 if(!name||!department||!Number.isInteger(id)||id<=0||!Number.isFinite(salary)||salary<0){$("formError").textContent="Enter a name, department, positive whole-number ID and valid salary.";return;}
 if(editingId===null&&employees.some(e=>e.id===id)){$("formError").textContent="That employee ID already exists.";return;}
 if(editingId!==null){Object.assign(employees.find(e=>e.id===editingId),{name,department,salary});toast("Employee updated");}
 else{employees.push({id,name,department,salary});toast("Employee added successfully");}
 saveEmployees();render();$("employeeDialog").close();
});
$("exportBtn").addEventListener("click",()=>{
 const rows=[["Employee ID","Name","Department","Monthly Salary"],...employees.slice().sort((a,b)=>a.id-b.id).map(e=>[e.id,e.name,e.department,e.salary])];
 const csv=rows.map(r=>r.map(v=>`"${String(v).replace(/"/g,'""')}"`).join(",")).join("\r\n");
 const url=URL.createObjectURL(new Blob([csv],{type:"text/csv;charset=utf-8;"})),a=document.createElement("a");a.href=url;a.download="employee-directory.csv";a.click();URL.revokeObjectURL(url);toast("CSV export ready");
});
render();
