(function(){
  var KEY = 'ruta-codigo-progreso';
  var TOTAL = 43;
  var BLOCKS = {
    c1: ['c101','c102','c103','c104','c105','c106','c107','c108','c109','c110','c111'],
    c2: ['c201','c202','c203','c204','c205','c206','c207','c208','c209','c210'],
    c3: ['c301','c302','c303','c304','c305','c306','c307','c308'],
    c4: ['c401','c402','c403','c404','c405','c406'],
    c5: ['c501','c502','c503','c504','c505','c506','c507','c508']
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
