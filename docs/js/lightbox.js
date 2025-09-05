document.addEventListener('DOMContentLoaded', function() {
      const lightbox = document.getElementById('lightbox');
      const lightboxImg = document.getElementById('lightbox-img');
      const closeBtn = document.querySelector('.lightbox-close');
      document.querySelectorAll('img.lightbox-img').forEach(img => {
        img.addEventListener('click', function() {
          lightboxImg.src = this.src;
          lightboxImg.alt = this.alt;
          lightbox.style.display = 'block';
          document.body.style.overflow = 'hidden';
        });
      });
      closeBtn.addEventListener('click', function() {
        lightbox.style.display = 'none';
        document.body.style.overflow = 'auto';
      });
      lightbox.addEventListener('click', function(e) {
        if (e.target === lightbox) {
          lightbox.style.display = 'none';
          document.body.style.overflow = 'auto';
        }
      });
      document.addEventListener('keydown', function(e) {
        if (e.key === 'Escape' && lightbox.style.display === 'block') {
          lightbox.style.display = 'none';
          document.body.style.overflow = 'auto';
        }
      });
    });
