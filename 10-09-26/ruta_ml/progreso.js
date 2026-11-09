(function(){
  var KEY = 'ruta-ml-progreso';
  var TOTAL = 48;
  var BLOCKS = {
    m1: ['m101','m102','m103','m104','m105','m106','m107','m108'],
    m2: ['m201','m202','m203','m204','m205','m206','m207','m208','m209','m210','m211','m212','m213'],
    m3: ['m301','m302','m303','m304','m305','m306','m307','m308','m309','m310','m311','m312'],
    m4: ['m401','m402','m403','m404','m405','m406','m407'],
    m5: ['m501','m502','m503','m504','m505','m506','m507','m508']
  };

  function load(){ try{ return JSON.parse(localStorage.getItem(KEY) || '{}'); }catch(e){ return {}; } }
  function save(state){ try{ localStorage.setItem(KEY, JSON.stringify(state)); }catch(e){} }
  var state = load();
  function countDone(ids){ return ids.filter(function(id){ return !!state[id]; }).length; }

  function applyState(){
    var doneCount = 0;
    Object.keys(BLOCKS).forEach(function(b){ doneCount += countDone(BLOCKS[b]); });
    document.querySelectorAll('input[type=checkbox][data-t]').forEach(function(cb){
      var id = cb.getAttribute('data-t');
      var isDone = !!state[id];
      cb.checked = isDone;
      var el = document.getElementById(id);
      if(el) el.classList.toggle('done', isDone);
    });
    var fracEl = document.getElementById('global-frac');
    if(fracEl) fracEl.textContent = doneCount + '/' + TOTAL;
    document.querySelectorAll('[data-block-frac]').forEach(function(el){
      var b = el.getAttribute('data-block-frac');
      if(BLOCKS[b]) el.textContent = countDone(BLOCKS[b]) + '/' + BLOCKS[b].length;
    });
  }
  document.querySelectorAll('input[type=checkbox][data-t]').forEach(function(cb){
    cb.addEventListener('change', function(){
      state[cb.getAttribute('data-t')] = cb.checked;
      save(state);
      applyState();
    });
  });
  applyState();
})();
